#include <iostream>
#include <cmath>
#include <armadillo>

// #include "functions.h"

// using namespace std;

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


//finding the max element in the matrix
double getMax(arma::mat A, int n) {
	double max;
	//only checking the upper triangular part
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){

			double aij = fabs(A(i,j));

			if (aij > max) {
				max = aij;

			}
		}

	}

	return max;
}


//function that computes the analytic eigenvalues of a toeplitz tridiagonal matrix
arma::vec AnalyticEigenvalues(int n, double rho_0, double rho_n){

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

