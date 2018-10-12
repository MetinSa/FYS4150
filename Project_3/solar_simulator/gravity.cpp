#include "functions.h"

// Defining gravityclass

Gravity::Gravity(Planetary_body *a, Planetary_body *b)
{
	alpha = a;
	beta = b;
	G = 4*pi*pi;
}
void Gravity::calcForce()
{
	double* R1 = alpha->getr();
	double* R2 = beta->getr();
	double F[3];
	double negF[3];

	double length = 0;

	for (int i = 0; i<3; i++){
		length += pow(R2[i] - R1[i], 2);
	}
	length = sqrt(length);

	for (int i = 0; i<3; i++){
		F[i] = (R2[i]-R1[i])*G*alpha->getm()*beta->getm()/pow(length, 3);
		negF[i] = -F[i];
	}
	alpha->addF(F);
	beta->addF(negF);

}
