#include <iostream>
#include <cmath>
#include <armadillo>
#include "functions.cpp"

using namespace std;

//main program which takes a matrix A and extracts the eigenvalues through the Jacobi method.
int main(int argc, char *argv[]){

	//reading in commandline arguments (rho_0, rho_n, n)
	int n;
	double rho_0, rho_n;

	if (argc < 4){

		cout << "Bad Usage: Please include the number of gid points n, rho_0 and rho_n. 3 arguments total. " << endl;
		exit(1);

	}

	else {

		n = atoi(argv[1]);
		rho_0 = atof(argv[2]);
		rho_n = atof(argv[3]);

	}

	//initializing initial matrix A, and identity matrix R
	arma::mat A(n,n);
	arma::mat R(n,n);

	//constructing the matrices
	R.eye(n,n);
	A = constructA(rho_0, rho_n, n);

	//initializing element positions k, l, number of itterations it, and max allowed itterations max it
	int k, l, it, max_it;
	double max, eps;

	//starting iteration
	it = 0;

	//starting max value
	max = getMax(A, k, l, n);

	//maximum number of iterations we allow
	max_it = n*n*n;

	//tolarance for the non-diag elements
	eps = 1.0E-8;

	//jacobi method 
	while (max > eps && it <= max_it) {

		jacobiRotate(A, R, k, l, n);
		max = getMax(A, k, l, n);
		it++;
	}

	cout << max <<endl;
	cout << it << endl;

	A.print("new A:");
	R.print("R :");

	arma::vec eigval;
	arma::eig_sym(eigval, A);

	eigval.print("arma eig: ");

	return 0;
}