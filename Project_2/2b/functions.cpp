#include <iostream>
#include <cmath>
#include <armadillo>

// #include "functions.h"

// using namespace std;

// constructing the matrix A
arma::mat constructA(double &rho_0, double &rho_n, int n){

	//making empty matrix
	arma::mat A = arma::mat(n,n);
	A.zeros();

	//steplength calculated from given rho values and gridpoints
	double h = (rho_n - rho_0)/n;

	//constant values which will fill the matrix
	double d = 2/(h*h);
	double a = -1/(h*h);

	//filling the tridiagonal matrix
	for (int i = 0; i < n; i++){
		//main diagonal
		A(i,i) = d;

		// off diagonal
		if (i != 0){
			A(i,i-1) = a;
		}

		if (i != n-1){
			A(i,i+1) = a;
		}

	}

	return A;

}


//finding the max element in the matrix
double getMax(arma::mat &A, int &k, int &l, int n) {

	//initializing the max value
	double max;

	//only checking the upper triangular part
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){

			double aij = fabs(A(i,j));

			if (aij > max) {
				max = aij;
				k = i;
				l = j;

			}
		}

	}

	return max;
}



//jacobi rotation algorithm
void jacobiRotate(arma::mat &A, arma::mat &R, int &k, int &l, int n ){

	//initializing sin(angle) and cos(angle)
	double s, c;

	//if matrix element is non zero
	if ( A(k,l) != 0.0) {

		// initializing t = tan(angle) and tau = cot 2(angle)
		double t, tau;
		tau = (A(l,l) - A(k,k))/(2*A(k,l));

		// making sure t works for large values of tau
		if (tau >= 0){
			t =  1.0/(tau + sqrt(1 + tau*tau));

		}

		else {
			t = -1.0/(-tau + sqrt(1 + tau*tau));

		}

		c = 1.0/(sqrt(1 + t*t));
		s = c*t;

	}
	//if matrix element is zero, sin(angle) = 0, cos(angle) = 1
	else {
		c = 1.0;
		s = 0.0;

	}

	// performing the rotation

	//initializing elements to be rotated
	double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
	a_kk = A(k,k);
	a_ll = A(l,l);

	//general expressions for the matrix elements
	A(k,k) = a_kk*c*c - 2*A(k,l)*c*s +a_ll*s*s;
	A(l,l) = a_ll*c*c + 2*A(k,l)*c*s +a_kk*s*s;
	A(k,l) = 0.0;
	A(l,k) = 0.0;

	//special index cases 
	for ( int i = 0; i < n; i++) {
		if ( i != k && i != l){

			a_ik = A(i,k);
			a_il = A(i,l);
			A(i,k) = a_ik*c - a_il*s;
			A(i,l) = a_il*c + a_ik*s;

			//making the matrix symmetric
			A(k,i) = A(i,k);
			A(l,i) = A(i,l);

		}

		//making eigenvectors
		r_ik = R(i,k);
		r_il = R(i,k);

		R(i,k) = r_ik*c - r_il*s;
		R(i,l) = r_il*c + r_ik*s;

	}

}








// //function that computes the analytic eigenvalues of a toeplitz tridiagonal matrix
// arma::vec AnalyticEigenvalues(double rho_0, double rho_n, int n){

// 	//making empty lambda
// 	arma::vec lambda = arma::vec(n);
// 	lambda.zeros();

// 	//defining stepsize
// 	double h = (rho_n - rho_0)/n;

// 	//using analytic function to find eigen values for the matrix A
// 	for (int i = 0; i < n; i++){
// 		lambda(i) = (2/h*h) - (2/(h*h))*cos(((i+1)*M_PI)/(n+1));
// 	}

// 	return lambda;
// }

