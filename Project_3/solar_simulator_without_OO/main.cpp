#include <iostream>
#include <iomanip>
#include "armadillo"
#include <fstream>
#include <sstream>

using namespace arma;
using namespace std;



int main()
{
double t_max = 10;          // Number of years
int N = 1e4;                // Number of iterations
double h = t_max/N;         // Step size
double r = 1.0;             // Radius or distance between the Sun and the Earth [AU]
double pi = 3.14159265359;

// Defining vectors
vec t(N+1);
vec x(N+1);
vec y(N+1);
vec vx(N+1);
vec vy(N+1);

// Setting initial values
x(0) =  1.0;                       // [AU]
y(0) =  0.0;                       // [AU]

vx(0) = -5.712595804744874E-03;    // [AU/yr]
vy(0) = 1.627120685499318E-02;     // [AU/yr]


double a_const = - (4*pi*pi)/(r*r*r);

for (int i = 0; i < N; i++){
  // Update position
  x(i+1) = x(i) + h*vx(i) + h*h/2.0 * a_const*x(i);
  y(i+1) = y(i) + h*vy(i) + h*h/2.0 * a_const*y(i);

  // Update velocity
  vx(i+1) = vx(i) + h/2*a_const*(x(i+1) + x(i));
  vy(i+1) = vy(i) + h/2*a_const*(y(i+1) + y(i));

  // Update time
  t(i+1) = t(i) + h;
}


// Write data  to file
ofstream myfile;
string name = "solarsystem.dat";
myfile.open (name.c_str());
myfile << "t:" << setw(15) << "x:" << setw(15) << "y:" << endl;

// printing to file using iomanip to setw and precision
for (int i = 0; i < N+1; i++){
  myfile << setprecision(7) << t(i) << setw(16) << setprecision(7) << x(i) << setw(16) << setprecision(7) << y(i) << endl;
}
myfile.close();
}
