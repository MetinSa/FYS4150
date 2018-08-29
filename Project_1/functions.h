#ifndef FUNCTIONS_H
#define FUNCTIONS_H

double func(double x){

	// The function f(x).

	return 100*exp(-10*x); 


}

double analytical_sol(double x){

	// The closed-form solution to -u''(x) = f(x).

	return 1.0 - (1 - exp(-10))*x - (exp(-10 * x));

}

#endif