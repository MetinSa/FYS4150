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
  { 	int expo;	double a_fill;	double b_fill;	double c_fill;

      // Reading in values from the command line
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


    int n = pow(10.0, expo);
    double x_0 = 0;    double x_n = 1;   // Boundary conditions
    double h = (x_n - x_0)/n;            // Step size
    double hh = h*h;

    vec x(n+1);                          // X-array from x_0 = 0 to x_n = 1 with steplength h
    vec a(n+1);                          // Lower secondary diagonal a
    vec b(n+1);                          // Main diagonal b
    vec c(n+1);                          // Upper secondary diagonal c
    vec f(n+1);                          // Source term f
    vec exact(n+1);                      // Exact solution

    vec b_tilde(n+1);                    // Diagonal elements after gaussian ellimination
    vec f_tilde(n+1);                    // Source term after gaussian ellimination
    vec u(n+1);                          // Solution


    // Filling x, a, b, c and calculating f and exact.
    for (int i = 0; i < n+1; i++){
      x(i) = x_0 + i*h;
      a(i) = a_fill;
      b(i) = b_fill;
      c(i) = c_fill;
      f(i) = func(x(i))*hh;
      exact(i) = exact_solution(x(i));
      }


    // Setting initial conditions for in the gauss eliminated results
     b_tilde(1) = b(1);
     f_tilde(1) = f(1);


    //starting the clock
  	clock_t start, finish;
  	start = clock();


    // Gaussian ellimination / forward substitution
    for (int i = 2; i < n; i++){
      double ab = a(i)/b_tilde(i-1);
      b_tilde(i) = b(i) - c(i-1)*ab;
      f_tilde(i) = f(i) - f_tilde(i-1)*ab;
      }


    // Setting endpoint of the backwards substitution
    u(n-1) = f_tilde(n-1)/b_tilde(n-1);


    // Backward substitution
    for (int i = n-2; i > 0; i--){
      u(i) = (f_tilde(i) - c(i)*u(i+1))/b_tilde(i);
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
