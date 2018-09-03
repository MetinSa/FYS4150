#include <iostream>
#include "armadillo"
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace arma;
using namespace std;


inline double f(double x) {return 100.*exp(-10*x);}
inline double exact_solution(double x) {return 1.-(1-exp(-10))*x-exp(-10*x);}


int main(int argc, char** argv)
  { int n = atoi(argv[1]);
    double x_0 = 0;    double x_n = 1;           // Boundary conditions
    double h = (x_n - x_0)/n;                    // Step size

    vec x(n+1);
    vec d(n+1);
    vec e(n+1);
    vec b(n+1);
    vec exact(n+1);

    for (int i = 0; i < n+1; i++){
      x(i) = x_0 + i*h;
      d(i) =  2;
      e(i) = -1;
      b(i) = f(x(i))*pow (h, 2.);
      exact(i) = exact_solution(x(i));
      }

    // Gaussian ellimination / forward substitution
    vec d_tilde(n+2); d_tilde(1) = d(1);
    vec b_tilde(n+2); b_tilde(1) = b(1);

    for (int i = 2; i < n+1; i++){
      d_tilde(i) = d(i) - pow(e(i-1),2)/d_tilde(i-1);
      b_tilde(i) = b(i) - (b_tilde(i-1)*e(i-1))/d_tilde(i-1);
      }

    // Backward substitution
    vec u(n+1); u(n) = b_tilde(n)/d_tilde(n);

    for (int i = n-1; i > 0; i--){
      u(i) = (b_tilde(i) - e(i)*u(i+1))/d_tilde(i);
    }


    // Write to file
    ofstream myfile;
    myfile.open ("data.txt");
    myfile << setprecision(10) << fixed;
    myfile << "x" << setw(15) << "u" << setw(19) << "exact" << endl;
    for (int i = 0; i < n+1; i++){
    myfile << x(i) << setw(15)  <<   u(i) << setw(15)  <<  exact(i) << endl;
    }
    myfile.close();
  }
