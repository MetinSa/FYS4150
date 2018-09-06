#include <iostream>
#include <iomanip>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace arma;
using namespace std;

// MUST BE COMPILED WITH LARMADILLO (ex: >c++ -o exec code.cpp -O1 -larmadillo)

// Source term
inline double func(double x) {return 100.*exp(-10*x);}

// Exact slution to the problem
inline double exact_solution(double x) {return 1.-(1-exp(-10))*x-exp(-10*x);}



int main(int argc, char** argv)
  { 	
    int n;

    // Reading in values from the command line
    if ( argc < 2)
    {
  		cout << "Bad Usage: Please include the power of 10^n.";
  		exit(1);
  	}
    
    if (string(argv[1]) == "test")
    {
      n = 4;
    }
    else
    {
      n = pow(10.0, atoi(argv[1]));
    }

  	
    // Load diagonals from command line

    double *vecfill = new double[n*2-1];

    for(int i = 0; i<n*2-1; i++)
    {
      vecfill[i] = 0;
    }

    for(int i = 0; i<argc-2; i++)
    {
      vecfill[i] = atof(argv[i+2]);
    }
    
    
    mat L, U;    // Assign armadillo matrices, lower and upper triangular for LU decomposition

    mat A(n, n); // Assign matrix to be decomposed
    A.fill(0);

    for (int i = 0; i<n; i++)
    {
    	A(i,i) = 2;
    	if (i != 0)
    	{
    		A(i,i-1) = -1;
    	}
    	if(i != n-1)
    	{
    		A(i, i+1) = -1;
    	}
    }

    //cout << "A:\n" << A << endl << endl;

    double x_0 = 0;    double x_n = 1;   // Boundary conditions
    double h = (x_n - x_0)/n;            // Step size

    vec b(n); vec z(n); vec x(n); vec c(n); vec exac(n);
    double sum;

    for (int i = 0; i < n; i++)
    {
      x(i) = x_0 + i*h;
      b(i) = func(x(i))*h*h;
      exac(i) = exact_solution(x(i));
    }

    //starting the clock
  	clock_t start, finish;
  	start = clock();

    lu(L, U, A);   // LU-decomposition

    //cout << "Upper triangular:\n" << U << endl << endl;
    //cout << "Lower triangular:\n" << L << endl;

    // Solving Ac = b => LUc = b => Lz = b => Uc = z
    // Forward substitution, finding Z
    z(0) = b(0);
    for (int i = 1; i<n; i++)
    {
    	z(i) = b(i) - L(i,i-1)*b(i-1);
    }


    c(n-1) = z(n-1)/L(n-1,n-1);
    for (int i = n-2; i == 0; i--)
    {
    	c(i) = z(i)/L(i,i) - z(i+1)*L(i,i+1);
    }


    // Stopping the clock
  	finish = clock();
  	double timeused = (double) (finish - start)/(CLOCKS_PER_SEC);
  	// printing the time used
  	cout << "Time used: " << timeused << " seconds" << endl;

  	// Writing the data to file
  	ofstream ofile;
	string name = "data_" + to_string(n) + "_c.dat";
	ofile.open(name);
	ofile << n << endl << endl;
	ofile << "x:" << setw(15) << "u:" << setw(15) << "v:" << endl;

	

	// printing to file using iomanip to setw and precision
	for (int i = 0; i < n; i++){
		ofile << setprecision(7) << x[i] << setw(16) << setprecision(7) << exac[i] << setw(16) << setprecision(7) << c[i] << endl;
	}

	

	ofile.close();


    return 0;
  }
