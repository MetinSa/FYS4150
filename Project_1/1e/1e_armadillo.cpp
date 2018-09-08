#include <iostream>
#include <iomanip>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace arma;
using namespace std;

// MUST BE COMPILED WITH LARMADILLO (ex: >c++ -o exec code.cpp -O1 -larmadillo)

// defining the outputfile as a global variable
ofstream ofile;

// computing the input function f.
inline double func(double x){ return 100.0*exp(-10*x);
}

// computing the exact solution to the problem
inline double analytic_sol(double x){ return 1.0 - (1 - exp(-10))*x - (exp(-10 * x));
}



int main(int argc, char** argv)
  { 	
	// declaring the exponent of 10 and the content of the diagonal vectors
	int expo;

	if ( argc <= 1) {
		cout << "Bad Usage: Please include the power of 10^n." << endl;
		exit(1);
	}
		else{
		expo = atoi(argv[1]);

	}
	// computing n based on the input exponent
	int n = pow(10.0,expo);

	// defining step length and its square
	double h = 1.0/(n);
	double hh = h*h;

	// Allocating memory to the vectors used in the algorithm
	vec x(n+1);			// x-array goes from [0,1] with steplength h
	mat A(n+1,n+1);		// banded matrix
	vec f(n+1);			// RHS solution f
	vec u(n+1);			// numerical solution
	vec v(n+1);			// analytical solution

	// filling the x and computing f and u
	for (int i = 0; i < n+1; i++){
		x[i] = i*h;
		f[i] = hh*func(x[i]);
		v[i] = analytic_sol(x[i]);
	}

	//creating the diagonal matrix
	
	for (int i = 0; i < n+1; i++){
		A(i,i) = 2;
		if (i != 0)
		{
			A(i,i-1) = -1;
		}
		if (i != n)
		{
			A(i,i+1) = -1;
		}
	}

	//starting the clock
	clock_t start, finish;
	start = clock();

	u = solve(A,f);

	// stopping the clock
	finish = clock();
	double timeused = (double) (finish - start)/(CLOCKS_PER_SEC);
	// printing the time used
	cout << "Time used: " << timeused << " seconds" << endl;

	// Writing the data to file
	string name = "data_" + to_string(n) + "_e.dat";
	ofile.open(name);
	ofile << n << endl << endl;
	ofile << "x:" << setw(15) << "u:" << setw(15) << "v:" << endl;

	

	// printing to file using iomanip to setw and precision
	for (int i = 0; i < n+1; i++){
	 	ofile << setprecision(7) << x[i] << setw(16) << setprecision(7) << u[i] << setw(16) << setprecision(7) << v[i] << endl;
	}

	ofile.close();

	// Saving time spent on algorithm
	ofile.open("time_e.dat",ios_base::app | ios_base::out);
	ofile << timeused << endl;
	ofile.close();
	

	return 0;
}
   
