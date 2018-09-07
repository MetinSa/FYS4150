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
inline double exact_solution(double x) {return 1.0-(1-exp(-10))*x-exp(-10*x);}




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

    mat A = zeros<mat>(n+1,n+1);         // A matrix
    vec x(n+1);                          // X-array from x_0 = 0 to x_n = 1 with steplength h
    vec f(n+1);                          // Source term f
    vec exact(n+1);                      // Exact solution


    //Filling x and calculating f and exact.
    for (int i = 1; i < n+1; i++){
       x(i) =  i*h;//x(i-1)+h;
       f(i) = func(x(i))*hh;
       exact(i) = exact_solution(x(i));
       }


    // Filling the matrix A
    A(1,1) = 2.0; A(1,2) = -1;

    for (int i = 2; i < n-1; i++){
      A(i,i-1) = -1.0;
      A(i,i) = 2.0;
      A(i,i+1) = -1.0;
      }

      A(n-1,n-1) = 2.0; A(n-1,n-2) = -1; A(n-2,n-1) = -1;


      // Solving Au = f
      vec u = solve(A,f);


      // Convert the integer n to string
      stringstream ss;
      ss << n;
      string n_str = ss.str();


      // Write data  to file
      ofstream myfile;
      string name = "data_" + n_str + "_e.dat";
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
