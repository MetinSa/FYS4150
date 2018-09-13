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


arma::vec Analytic_Eigenvalues(int n){
	//function that computes the analytic eigenvalues of a toeplitz tridiagonal matrix

	//making empty lambda
	arma::vec lambda = arma::vec(n);
	lambda.zeros();

	//defining stepsize
	double h = (rho_n - rho_0)/n;

	//using analytic function to find eigen values for the matrix A
	for (int i = 0; i < n; i++){
		lambda(i) = (2/h*h) - 2*(1/(h*h))*cos((i*M_PI)/(n+1));
	}

	return lambda;
}



int main(int argc, char *argv[]){

	//reading in number of gridpoints
	int n = atoi(argv[1]);
	double rho_0 = atof(argv[2]);
	double rho_n = atof(argv[3]);

	arma::mat A(n,n);
	arma::mat lambda(n,n);

	A = constructA(n, rho_0, rho_n);
	lambda = Analytic_Eigenvalues(n, rho_0, rho_n);
	lambda.print("lambda: ");

	
	return 0;
}