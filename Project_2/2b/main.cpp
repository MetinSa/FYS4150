#include <iostream>
#include <cmath>
#include <armadillo>
#include <ctime>
#include "functions.h"

using namespace std;

// Main program which diagonalizes a given matrix using Jacobi's algorithm
int main(int argc, char *argv[]){

	// Reading in commandline arguments (rho_0, rho_n, n)
	int n;
	double rho_0, rho_n;

	// Checking if the correct commandline arguments are used when compiling
	if (argc < 4){

		cout << "Bad Usage: Please include 'n', 'rho_0' and 'rho_n'. 3 arguments in total. " << endl;
		exit(1);
	}

	else {

		n = atoi(argv[1]);
		rho_0 = atof(argv[2]);
		rho_n = atof(argv[3]);
	}

	// Initializing matrix A, and identity matrix R, and the Eigenvalues of A
	arma::mat A(n,n);
	arma::mat R(n,n);
	arma::vec eigval(n);
	R.eye(n,n);

	// Starting the timer
	clock_t start = clock();

	// Constructing matrix A
	A = constructA(rho_0, rho_n, n);

	// Initializing quantities to be used in diagonalization process
	int k, l, N_it;

	// Diagonalizing matrix A using Jacobi's rotation method
	diagJacobi(A, R, k, l, N_it, n);


	// Stopping the timer
	clock_t stop = clock();

	// Extracting the eigenvalues from the diagonal and sorting
	eigval = A.diag();
	eigval = arma::sort(eigval);

	// Printing the results of the diagonalization
	cout << "============================" << endl;
	cout << "Eigenvalues of matrix A: " << endl;
	cout << "============================" << endl;
	cout << eigval << endl;
	cout << "============================" << endl;
	cout << "Number of transformations: " << N_it << endl;
	cout << "============================" << endl;
	cout << "Time used computing: " << (double) (stop-start)/CLOCKS_PER_SEC << "seconds" << endl;
	cout << "============================" << endl;

	return 0;
}