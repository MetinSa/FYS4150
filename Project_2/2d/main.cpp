#include <iostream>
#include <cmath>
#include <armadillo>
#include <ctime>
#include <fstream>
#include "functions.h"

using namespace std;

// Main program which diagonalizes a given matrix using Jacobi's algorithm
int main(int argc, char *argv[]){

	// Reading in commandline arguments (rho_0, rho_n, n)
	int n;
	double rho_0 = 0.0;
	double rho_n;

	// Checking if the correct commandline arguments are used when compiling
	if (argc < 3){

		cout << "Bad Usage: Please include 'n' and 'rho_n'. 2 arguments in total. " << endl;
		exit(1);
	}

	else {

		n = atoi(argv[1]);
		rho_n = atof(argv[2]);
	}

	// Initializing matrix A, and identity matrix R, and the Eigenvalues of A
	arma::mat A(n,n);
	arma::mat R(n,n);
	arma::vec eigval(n);
	R.eye(n,n);

	// Constructing matrix A
	A = constructA(rho_0, rho_n, n);

	// Initializing quantities to be used in diagonalization process
	int k, l, N_it, ground_state;

	// Diagonalizing matrix A using Jacobi's rotation method
	diagJacobi(A, R, k, l, N_it, ground_state, n);

	// Writing the groundstate eigenvector to file
	string filename = "eigenvectors.dat";
	toFile(R, filename, ground_state);



	return 0;
}