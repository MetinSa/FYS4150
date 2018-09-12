#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;

// constructing the matrix A
arma::mat constructA(int n, double rho_0, double rho_n){

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

int main(int argc, char *argv[]){

	//reading in number of gridpoints
	int n = atoi(argv[1]);
	double rho_0 = atof(argv[2]);
	double rho_n = atof(argv[3]);

	arma::mat A(n,n);

	A = constructA(n, rho_0, rho_n);
	A.print("A: ");

	return 0;
}