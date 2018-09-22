#include <iostream>
#include <cmath>
#include <armadillo>
#include "functions.cpp"

using namespace std;

int main(int argc, char *argv[]){

	//reading in number of gridpoints
	int n = atoi(argv[1]);
	double rho_0 = atof(argv[2]);
	double rho_n = atof(argv[3]);

	//initializing matrices and vecotors to be used
	arma::mat A(n,n);
	arma::mat R(n,n);
	R.eye(n,n);
	R.print("R: ");


	A = constructA(rho_0, rho_n, n);
	A.print("A: ");

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

	while (max > eps && it <= max_it) {

		jacobiRotate(A, R, k, l, n);
		max = getMax(A, k, l, n);
		it++;
	}

	cout << max <<endl;
	cout << it << endl;



	return 0;
}