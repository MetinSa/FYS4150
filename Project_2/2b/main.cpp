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

	//constructing matrix A, and identity matrix R
	arma::mat A(n,n);
	arma::mat R(n,n);
	R.eye(n,n);

	A = constructA(rho_0, rho_n, n);

	// diagonalizing matrix A
	int k, l;
	diagJacobi(A, R, k, l, n);

	//printing the eigenvalues
	cout << "============" << endl;
	cout << "Eigenvalues: " << endl;
	cout << "============" << endl;
	for (int i = 0; i < n; i++){

		cout << A(i,i) << endl;

	}
	cout << "============" << endl;

	return 0;
}