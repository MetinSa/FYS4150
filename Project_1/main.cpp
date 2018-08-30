#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <fstream>
#include "functions.h"

using namespace std;

// defining the outputfile as a global variable
ofstream ofile;


// Main algorithm
int main(int argc, char *argv[]){

	//starting by defining number of grid points n from the command line
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
	double *v = new double[n+2];			// analytical solution

	// filling the x-array, where x_i = x0 + i*h and also the diagonal vectors of matrix A
	for (int i = 0; i < n+2; i++){
		x[i] = x_0 + i*h;
		e[i] = -1;
		d[i] = 2;

	}

	//solving b = h^2 * f along with the analytic solution u
	for (int i = 0; i < n+1; i++){
		b[i] = h*h * func(x[i]);
		v[i] = analytical_sol(x[i]);

	}


	// Forward Substitution

	//setting the initial conditions
	d_tilde[1] = d[1];
	b_tilde[1] = b[1];

	// computing equatino (1) and (2) from the lecture notes
	for (int i = 2; i < n+1; i++){
		d_tilde[i] = d[i] - (pow(e[i-1], 2)/d_tilde[i-1]);
		b_tilde[i] = b[i] - ((b_tilde[i-1]*e[i-1])/d_tilde[i-1]);

	}


	// Backwards Substitution

	//setting the initial conditions
	u[n] = b_tilde[n]/d_tilde[n];

	// computing equation (3) with a reversed loop
	for (int i = n-1; i > 0; i--){
		u[i] = (b_tilde[i] - e[i]*u[i+1])/(d_tilde[i]);

	}

	// stopping the clock
	finish = clock();
	double timeused = (double) (finish - start)/(CLOCKS_PER_SEC);

	// printing the time used
	cout << "Time used: " << timeused << " seconds" << endl;


	// printing the relative error
	double max = error_estimation(n, u, v);
	cout << "max relative error: " << max << endl;


	// Writing the data to file
	string name = "data_" + to_string(n) + ".dat";
	ofile.open(name);
	ofile << n << endl << endl;
	ofile << "x:" << setw(15) << "u:" << setw(15) << "v:" << endl;


	// printing to file using iomanip to setw and precision
	for (int i = 0; i < n+2; i++){
		ofile << setprecision(7) << x[i] << setw(16) << setprecision(7) << u[i] << setw(16) << setprecision(7) << v[i] << endl;

	}

	ofile.close();



	// freeing up memory
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