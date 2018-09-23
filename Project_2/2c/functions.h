//==================================
// making guard
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//==================================
// including includes

#include <iostream>
#include <cmath>
#include <armadillo>


//==================================
// declearing functions

arma::mat constructA(double rho_0, double rho_n, int n);
double getMax(arma::mat A, int &k, int &l, int n);
void jacobiRotate(arma::mat &A, arma::mat &R, int k, int l, int n);
void diagJacobi(arma::mat &A, arma::mat &R, int k, int l, int &N_it, int n );

//==================================


#endif