#include "catch.hpp"
#include "functions.h"

TEST_CASE("Testing max value of Toeplitz matrix") {

	// Testing for 5 x 5 matrix with rho_0 = 3 and rho_n = 7
	int n = 5;
	double rho_0 = 3;
	double rho_n = 7;

	// The above values willl result in a max element of -1.5625
	double analytic_max = -1.5625;

	// Initializing matrix A
	arma::mat A(n,n);

	// Constructing matrix A
	A = makeTridiagonal(rho_0, rho_n, n);

	// Extracting max value from matrix
	int k, l;
	double max;
	max = getMax(A, k, l, n);

	// Comparing max values using catch
	REQUIRE(k == 0);
	REQUIRE(l == 1);
	REQUIRE(max == Approx(fabs(analytic_max)));

}


TEST_CASE("Testing eigenvalues of Toeplitz matrix") {

	// Testing for 10 x 10 matrix
	int n = 10;

	// Computing exact analytic eigenvalues for a Toeplitz matrix
	double pi = M_PI;
	arma::vec exact(n);

	// Steplength
	double h = 1.0/n;

	// Main diagonal and secondary diagonal constants
	double d = 2.0/(h*h);
	double a = -1.0/(h*h);

	// Computing exact eigenvalues
	for (int i = 0; i < n; i++){

		exact(i) = d + 2*a*cos(((i+1)*pi)/(n+1));
	}

	// Get eigenvalues from Jacobi method for comparison
	// Initializing matrix A, and identity matrix R, and the Eigenvalues of A
	arma::mat A(n,n);
	arma::mat R(n,n);
	arma::vec eigval(n);
	R.eye(n,n);

	// Constructing matrix A
	double rho_0 = 0; 
	double rho_n = 1;
	A = makeTridiagonal(rho_0, rho_n, n);

	// Initializing quantities to be used in diagonalization process
	int k, l, N_it;

	// Diagonalizing matrix A using Jacobi's rotation method
	diagJacobi(A, R, k, l, N_it, n);

	// Extracting the eigenvalues from the diagonal and sorting
	eigval = A.diag();
	eigval = arma::sort(eigval);


	// Comparing all eigenvalues using catch
	for (int i = 0; i < n; i++){
		REQUIRE(eigval(i)==Approx(exact(i)).epsilon(0.00000001));
	}

}