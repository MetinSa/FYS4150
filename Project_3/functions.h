#ifndef FUNCTIONS_H
#define FUNCTIONS_H


// Including includes
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>


// define pi
const double pi  =3.141592653589793238463;

// Declaring Planetary_body class

class Planetary_body
{
	double r[3];
	double v[3];
	double F[3];
	double m;

public:
	Planetary_body(double *r_, double *v_, double &m_);
	void addF(double *aF);
	void setr(double *r_);
	void resetF();
	void integrate(double &dt);
	double getm();
	double* getr();
};

// Declaring Gravity class

class Gravity
{
	Planetary_body* alpha;
	Planetary_body* beta;
	double G;
public:
	Gravity(Planetary_body *a, Planetary_body *b);
	void calcForce();
};

#endif
