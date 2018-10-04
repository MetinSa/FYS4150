#include "functions.h"

/*
Usage:
Planetary body class:	Class for each planetary body. Has constructor to set initial position and velocity, and mass.
						Has functions for reseting F, adding F and integrating.

Gravity class:			Has two planetary body classes as input. Has function to calculate the gravitatonal force
						between them.

The idea is to put all planetary bodies we want to simulate in an array of planetary body-classes, and then create an
array of gravity-classes for every pair of planetary bodies. Then we can easily calculate the force and integrate
using a for-loop or the map-function.
*/

Gravity::Gravity(Planetary_body* a, Planetary_body* b)
{
	alpha = a;
	beta = b;
	G = 4*pi*pi;
}
void Gravity::calcForce()
{
	double R1[3] = alpha->r;
	double R2[3] = beta->r;
	double F[3];
	double negF[3];

	double length = 0;

	for (int i = 0; i<3; i++){
		length += pow(R2[i] - R1[i], 2);
	}
	length = sqrt(length);

	for (int i = 0; i<3; i++){
		F[i] = (R2[i]-R1[i])*G*alpha->m*beta->m/pow(length, 3);
		negF[i] = -F[i]
	}
	alpha->addF(F)
	beta->addF(negF)

}


Planetary_body::Planetary_body(double* r_, double* v_, double* F_, double m_)
{
	r = r_;
	v = v_;
	F = F_;
	m = m_;
}

void Planetary_body::addF(double* F_)
{
	for (int i = 0; i<3; i++){
		F[i] += F_[i];
	}

}

void Planetary_body::resetF()
{
	for (int i = 0; i<3; i++){
		F[i] = 0;
	}
}

void Planetary_body::integrate(double dt)
{
	//Euler-cromer
	for (int i = 0; i<3; i++){
		v[i] += (F[i]/m)*dt;
		r[i] += v[i]*dt;
	}
}