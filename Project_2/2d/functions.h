// Making guard
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Including includes
#include <iostream>
#include <cmath>
#include <armadillo>
#include <fstream>


// Declearing functions
arma::mat makeTridiagonal(double rho_0, double rho_n, int n);
double getMax(arma::mat A, int &k, int &l, int n);
void jacobiRotate(arma::mat &A, arma::mat &R, int k, int l, int n);
void diagJacobi(arma::mat &A, arma::mat &R, int k, int l, int &N_it, int &ground_state, int n);
void toFile(arma::mat R, std::string filename, int ground_state, int n, double rho_n);

#endif