#include "catch.hpp"
#include "functions.h"

TEST_CASE("Testing eigenvalues of Toeplitz matrix"){

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
	A = constructA(rho_0, rho_n, n);

	// Initializing quantities to be used in diagonalization process
	int k, l, N_it;

	// Diagonalizing matrix A using Jacobi's rotation method
	diagJacobi(A, R, k, l, N_it, n);

	// Extracting the eigenvalues from the diagonal and sorting
	eigval = A.diag();
	eigval = arma::sort(eigval);

	// Comparing eigenvalues using catch
	REQUIRE(eigval(0)==Approx(exact(0)).epsilon(0.00000001));
	REQUIRE(eigval(1)==Approx(exact(1)).epsilon(0.00000001));
	REQUIRE(eigval(2)==Approx(exact(2)).epsilon(0.00000001));

}