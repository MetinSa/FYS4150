#include "functions.h"


Planetary_body::Planetary_body(vec3 newPosition, vec3 newVelocity, double newMass, std::string newName)
{

	position = newPosition;
	velocity = newVelocity;
	mass = newMass;
	name = newName;
}

void Planetary_body::addF(vec3 addForce)
{

	force += addForce;

}

void Planetary_body::resetF()
{
	force = 0.;
}

void Planetary_body::integrate(double &dt)
{

	velocity += (force/mass) * dt;
	position += velocity * dt;
}
