#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

// defining the outputfile as a global variable
ofstream ofile;

// computing the input function f.
inline double func(double x){ return 100.0*exp(-10*x); 
}

// computing the exact solution to the problem
inline double analytic_sol(double x){ return 1.0 - (1 - exp(-10))*x - (exp(-10 * x));
}

// Main program

int main(int argc, char *argv[]){

	// declaring the exponent of 10 and the content of the diagonal vectors
	int expo;	double a_fill;	double b_fill;	double c_fill;

	if ( argc <= 4) {
		cout << "Bad Usage: Please include the power of 10^n, and the content of a, b and c diagonal vectors. Four total inputs." << endl;
		exit(1);
	}
		else{
		expo = atoi(argv[1]);
		a_fill = atoi(argv[2]);
		b_fill = atoi(argv[3]);
		c_fill = atoi(argv[4]);
	}
	// computing n based on the input exponent
	int n = pow(10.0,expo);

	// defining step length and its square
	double h = 1.0/(n);
	double hh = h*h;

	// Allocating memory to the vectors used in the algorithm
	double *x = new double[n+1];			// x-array goes from [0,1] with steplength h
	double *a = new double[n+1];			// secondary diagonal a
	double *b = new double[n+1];			// main diagonal b
	double *c = new double[n+1];			// secondary diagonal c
	double *f = new double[n+1];			// RHS solution f
	double *f_tilde = new double[n+1];		// RHS solution f_tilde
	double *u = new double[n+1];			// numerical solution	
	double *v = new double[n+1];			// analytical solution

	// filling the x, a, b and c arrays in addition to computing f and u
	for (int i = 0; i < n+1; i++){
		x[i] = i*h;
		a[i] = a_fill;
		b[i] = b_fill;
		c[i] = c_fill;
		f[i] = hh*func(x[i]);
		v[i] = analytic_sol(x[i]);
	}

	//starting the clock
	clock_t start, finish;
	start = clock();

	// forward substitution
	for (int i = 2; i < n; i++){
		b[i] = b[i] - (a[i]*c[i-1])/b[i-1];
		f_tilde[i] = f[i] - (a[i]*f_tilde[i-1])/b[i-1];
	}

	// backward substitution
	u[n-1] = f_tilde[n-1]/b[n-1];			// setting initial condition

	for (int i = n-2; i > 0; i--){
		u[i] = f_tilde[i] - (c[i]*u[i+1])/b[i];
	}	

	// stopping the clock
	finish = clock();
	double timeused = (double) (finish - start)/(CLOCKS_PER_SEC);
	// printing the time used
	cout << "Time used: " << timeused << " seconds" << endl;

	// Writing the data to file
	string name = "data_" + to_string(n) + ".dat";
	ofile.open(name);
	ofile << n << endl << endl;
	ofile << "x:" << setw(15) << "u:" << setw(15) << "v:" << endl;

	// printing to file using iomanip to setw and precision
	for (int i = 0; i < n+1; i++){
		ofile << setprecision(7) << x[i] << setw(16) << setprecision(7) << u[i] << setw(16) << setprecision(7) << v[i] << endl;
	}

	ofile.close();

	// freeing up memory
	delete [] x;
	delete [] a;
	delete [] b;
	delete [] c;
	delete [] f;
	delete [] f_tilde;
	delete [] u;
	delete [] v;

	return 0;
}