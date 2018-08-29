#include <iostream>
#include <armadillo>
#include <cmath>
#include <time.h>

using namespace std;
using namespace arma;


double function(double x){

	// The function f(x).

	return 100*exp(-10*x); 


}

double analytical_sol(double x){

	// The closed-form solution to -u''(x) = f(x).

	return 1 - (1 - exp(-10)) * x - exp(-10 * x);


}


// Main algorithm

int main(int argc, char *argv[]){

	//starting by defining n
	int n = atoi(argv[1]);

	//starting the clock
	clock_t start, finish;
	start = clock();

	// Defining boundary conditions
	double x_0 = 0;	double x_n = 1;

	// Defining step length
	double h = (x_n - x_0)/(n);

	// Allocating memory to the vectors used in the algorithm
	double *x = new double[n+2];			// x-array goes from [0,1] with steplength h
	double *e = new double[n+2];			// secondary diagonal
	double *d = new double[n+2];			// main diagonal
	double *b = new double[n+2];			// RHS solution 
	double *b_tilde = new double[n+2];		// RHS tilde solution
	double *d_tilde = new double[n+2];		// gauss eliminated main diagonal
	double *u = new double[n+2];			// numerical solution	
	double *v = new double[n+2];		// analytical solution

	// filling the x-array, where x_i = x0 + i*h and also the diagonal vectors of matrix A
	for (int i = 0; i < n+2; i++){
		x[i] = x_0 + i*h;
		e[i] = -1;
		d[i] = 2;
	}

	// printing test
	for (int i = 0; i < n+2; i++){
		cout << e[i] << " ";

	}





	delete [] x;
	delete [] e;
	delete [] d;
	delete [] b;
	delete [] b_tilde;
	delete [] d_tilde;
	delete [] u;
	delete [] v;

	return 0;
}