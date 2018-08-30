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



double error_estimation(int n, double u[], double v[]){

	// Calculating the error between the analytic and numerical results.

	double *eps =  new double[n+2];				// relative error array
	double max = 0.0;							// placeholder max error

	// calculating the relative error
	for (int i = 1; i < n+1; i++){
		eps[i] = log10(abs((v[i]-u[i])/u[i]));

		//finding the maximum
		if(abs(eps[i]) > abs(max)){
			max = eps[i];
		}
	}
	
	// freeing up memory
	delete [] eps;

	return max;
	

}





#endif