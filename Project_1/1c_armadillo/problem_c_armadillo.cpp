#include <iostream>
#include <iomanip>
#include "armadillo"
#include <cmath>
#include <fstream>
#include <sstream>

using namespace arma;
using namespace std;

// Source term
inline double func(double x) {return 100.*exp(-10*x);}

// Exact slution to the problem
inline double exact_solution(double x) {return 1.-(1-exp(-10))*x-exp(-10*x);}




int main(int argc, char** argv)
  { 	int expo;

      // Reading in values from the command line
    	if ( argc <= 1) {
  		cout << "Bad Usage: Please include the power of 10^n." << endl;
  		exit(1);
  	}
  		else{
  		expo = atoi(argv[1]);
  	}


    int n = pow(10.0, expo);
    double h = 1.0/n;                    // Step size
    double hh = h*h;

    vec x(n+1);                          // X-array from x_0 = 0 to x_n = 1 with steplength h
    vec f(n+1);                          // Source term f
    vec exact(n+1);                      // Exact solution

    vec b_tilde(n+1);                    // Diagonal elements after gaussian ellimination
    vec f_tilde(n+1);                    // Source term after gaussian ellimination
    vec u(n+1);                          // Solution


    // Filling x, a, b, c and calculating f and exact.
    for (int i = 0; i < n+1; i++){
      x(i) = i*h;
      f(i) = func(x(i))*hh;
      exact(i) = exact_solution(x(i));
      }

    // Setting initial conditions for in the gaussian eliminated results
    b_tilde(0) = b_tilde(n) = 2.0;

    // Precomputing the diagonal after gaussian elimination
    for (int i = 1; i < n; i++){
      b_tilde(i) = (i+1.0)/((double) i);
      }


    //starting the clock
  	clock_t start, finish;
  	start = clock();


    // Gaussian ellimination / forward substitution
    f_tilde(1) = f(1);
    for (int i = 2; i < n; i++){
      f_tilde(i) = f(i) + (f_tilde(i-1)/b_tilde(i-1));
      }

    // Setting endpoint of the backwards substitution
    u(n-1) = f_tilde(n-1)/b_tilde(n-1);


    // Backward substitution
    for (int i = n-2; i > 0; i--){
      u(i) = (f_tilde(i) + u(i+1))/b_tilde(i);
    }


    // Stopping the clock
  	finish = clock();
  	double timeused = (double) (finish - start)/(CLOCKS_PER_SEC);
  	// printing the time used
  	cout << "Time used: " << timeused << " seconds" << endl;


    // Convert the integer n to string
    stringstream ss;
    ss << n;
    string n_str = ss.str();


    // Write data  to file
    ofstream myfile;
    string name = "data_armadillo_" + n_str + ".dat";
    myfile.open (name.c_str());
    myfile << n << endl << endl;
  	myfile << "x:" << setw(15) << "u:" << setw(15) << "v:" << endl;

    // printing to file using iomanip to setw and precision
  	for (int i = 0; i < n+1; i++){
      myfile << setprecision(7) << x[i] << setw(16) << setprecision(7) << u[i] << setw(16) << setprecision(7) << exact[i] << endl;
    }
    myfile.close();


      return 0;
    }
