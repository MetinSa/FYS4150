#include <iostream>
#include <cmath>
#include <armadillo>
#include <fstream>

#include "functions.h"


// Constructing tridiagonal Toeplitz matrix A
arma::mat makeTridiagonal(double rho_0, double rho_n, double omega, int n) {

	// Initializing empty matrix A
	arma::mat A = arma::mat(n,n);
	A.zeros();

	// Steplength calculated from given rho values and number of gridpoints
	double h = (rho_n - rho_0)/(double)(n);

	// Second derivative diagonal constants
	double d = 2/(h*h);
	double a = -1/(h*h);

	// Initializing potential and rho
	double rho, V;

	for (int i = 0; i < n; i++){

		// Computing: rho = rho_0 + i*h, and potential V = rho^2
		rho = (i+1)*h;
		V = (omega*omega)*(rho*rho) + (1.0/rho);

		// Main diagonal with the addition of the harmonic potential
		A(i,i) = d+V;

		// Secondary diagonals
		if (i < n-1){
			A(i,i+1) = a;
			A(i+1,i) = a;
	
		}
	}

	return A;
}


// Extracting largest element in a symmetric matrix
double getMax(arma::mat A, int &k, int &l, int n) {

	// Initializing the max value
	double max;

	// Itterating through upper triangular of matrix
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){

			double aij = fabs(A(i,j));

			// Finding max value
			if (aij > max) {

				max = aij;
				k = i;
				l = j;

			}
		}
	}

	return max;
}


// Jacobi rotation algorithm
void jacobiRotate(arma::mat &A, arma::mat &R, int k, int l, int n) {

	// Initializing sin(angle) and cos(angle)
	double s, c;

	// If matrix element is non zero
	if ( A(k,l) != 0.0) {

		// Initializing t = tan(angle), and tau = cot 2(angle)
		double t, tau;
		tau = ( A(l,l) - A(k,k) )/( 2 * A(k,l) );

		// Plus-minus conditions
		if (tau >= 0) {
			t =  1.0/(tau + sqrt(1 + tau*tau));

		}

		else {
			t = -1.0/(-tau + sqrt(1 + tau*tau));

		}

		// Defining cos(angle) and sin(angle)
		c = 1.0/(sqrt(1 + t*t));
		s = c*t;

	}

	// If matrix element is zero, sin(angle) = 0, cos(angle) = 1
	else {
		c = 1.0;
		s = 0.0;

	}

	// =======================
	// Performing the rotation
	// =======================

	// Initializing variables to be used in rotation algortihm
	double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
	a_kk = A(k,k);
	a_ll = A(l,l);

	// General expressions for the matrix elements
	A(k,k) = a_kk*c*c - 2*A(k,l)*c*s +a_ll*s*s;
	A(l,l) = a_ll*c*c + 2*A(k,l)*c*s +a_kk*s*s;
	A(k,l) = 0.0;
	A(l,k) = 0.0;

	// Dealing with special index cases 
	for ( int i = 0; i < n; i++) {
		if ( i != k && i != l) {

			a_ik = A(i,k);
			a_il = A(i,l);
			A(i,k) = a_ik*c - a_il*s;
			A(i,l) = a_il*c + a_ik*s;

			// Making the matrix symmetric
			A(k,i) = A(i,k);
			A(l,i) = A(i,l);
		}

		// Making eigenvectors
		r_ik = R(i,k);
		r_il = R(i,l);

		R(i,k) = r_ik*c - r_il*s;
		R(i,l) = r_il*c + r_ik*s;

	}
}


// Diagonalizing a matrix using Jacobi's rotation algorithm
void diagJacobi(arma::mat &A, arma::mat &R, int k, int l, int &N_it, int &ground_state, int n) {

	// Restricting itterations
	int it = 0; 
	int max_it = n*n*n;

	// Tolarance for the non-diagonal elements
	double eps = 1.0E-10;

	// Initial max non diagonal value
 	double max;
 	max = getMax(A, k, l, n);

	// Performing the Jacobi rotation as long as conditions are met
	while (max > eps && it <= max_it) {

		jacobiRotate(A, R, k, l, n);
		max = getMax(A, k, l, n);
		it++;

	}

	// Extracting number of transformations
	N_it = it;

	// Finding ground state column (index of column in A with smallest eigenvalue)
	for (int i = 0; i < n; i++) {
		if (A(ground_state,ground_state) < A(i,i)) {

			ground_state = i;
		}
	}
}


// Writing the groundstate (smallest eigenvalue) to file
void toFile(arma::mat R, std::string filename, int ground_state, int n, double rho_n, double omega) {
	
	// Opening file
	std::ofstream ofile;
	ofile.open(filename);

	// Writing the number of grid points and rho_max
	ofile << n << std::endl;
	ofile << rho_n << std::endl << std::endl;
	ofile << omega << std::endl << std::endl;
	// Writing eigenvector corresponding to groundstate eigenvalue
	for (int i = 0; i < n; i++) {

		ofile << R(i, ground_state) << std::endl;
	}

	// Closing file
	ofile.close();
}
