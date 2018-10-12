#include "functions.h"


Planetary_body::Planetary_body(vec3 newposition, vec3 newvelocity, vec3 newMass, std::string newname)
{

	position = newposition;
	velocity = newvelocity;
	mass = newMass;
	name = newname;
}

void Planetary_body::addF(vec3 addForce)
{

	force += addforce;

}

void Planetary_body::resetF()
{
	F = 0.;
}

void Planetary_body::integrate(double &dt)
{

	v += (F/m) * dt;
	r += v * dt;
}

double Planetary_body::getm()
{
	return m;
}

vec3 Planetary_body::getr()
{
	return r;
}