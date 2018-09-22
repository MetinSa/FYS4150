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
	// double rho_0 = 0;
	// double rho_n = 1;

	//initializing matrix A
	arma::mat A(n,n);
	A = constructA(n, rho_0, rho_n);

	A.print("A:");

	return 0;
}