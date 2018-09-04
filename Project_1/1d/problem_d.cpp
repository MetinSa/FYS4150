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
	int expo;

	if ( argc <= 1) {
		cout << "Bad Usage: Please include the max power of 10^n." << endl;
		exit(1);
	}
		else{
		expo = atoi(argv[1]);

	}
	// computing n based on the input exponent
	for (int i = 1; i <= expo; i++){

		int n = pow(10.0,i);	

		// defining step length and its square
		double h = 1.0/(n);
		double hh = h*h;	

		// Allocating memory to the vectors used in the algorithm
		double *x = new double[n+1];			// x-array goes from [0,1] with steplength h
		double *d = new double[n+1];			// main diagonal renamed to d from b
		double *f = new double[n+1];			// RHS solution f
		double *f_tilde = new double[n+1];		// RHS solution f_tilde
		double *u = new double[n+1];			// numerical solution	
		double *v = new double[n+1];			// analytical solution	

		// filling the x, a, b and c arrays in addition to computing f and u
		for (int i = 0; i < n+1; i++){
			x[i] = i*h;
			f[i] = hh*func(x[i]);
			v[i] = analytic_sol(x[i]);
		}	

		//precomputing the diagonal
		d[0] = d[n] = 2.0;
		for (int i = 1; i < n; i++){
			d[i] = (i+1.0)/((double)i);
		}	

		//starting the clock
		clock_t start, finish;
		start = clock();	

		// forward substitution
		f_tilde[1] = f[1];
		for (int i = 2; i < n; i++){
			f_tilde[i] = f[i] + (f_tilde[i-1]/d[i-1]);
		}	
	

		// backward substitution
		u[n-1] = f_tilde[n-1]/d[n-1];			// setting initial condition	

		for (int i = n-2; i > 0; i--){
			u[i] = (f_tilde[i] + u[i+1])/d[i];
		}		

		// stopping the clock
		finish = clock();
		double timeused = (double) (finish - start)/(CLOCKS_PER_SEC);
		// printing the time used
		cout << "Time used: " << timeused << " seconds" << endl;	

		// estimating error
		double*eps = new double[n+1];
		double max = -20;	

		for (int i = 1; i < n; i++){
			eps[i] = log10(abs((v[i]-u[i])/u[i]));	

			if ( ( eps[i] > max) && (isinf(eps[i])== 0) ){
				max = eps[i];
			}

		}
	
		// appending the error to file
		ofile.open("error.dat", ios_base::app | ios_base::out);
		ofile << setprecision(7) << n << setw(16) << setprecision(7) << max << endl;
			

		ofile.close();	

		// freeing up memory
		delete [] x;
		delete [] d;
		delete [] f;
		delete [] f_tilde;
		delete [] u;
		delete [] v;
		delete [] eps;

		cout << "n: " << n << " finished" << endl;
	}

	return 0;
}