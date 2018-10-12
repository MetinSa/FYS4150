#include "functions.h"

// Defining gravityclass

Gravity::Gravity(PlanetaryBody *a, PlanetaryBody *b)
{
	alpha = a;
	beta = b;
	G = 4*pi*pi;
}
void Gravity::calcForce()
{
	vec3 R1 = alpha->position;
	vec3 R2 = beta->position;
	vec3 F;

	double length = (R2-R1).length();


	F = (R2-R1)*G*alpha->mass*beta->mass/pow(length, 3);
	
	alpha->addF(F);
	beta->addF(F-F-F);

}
