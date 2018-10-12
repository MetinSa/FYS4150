#include "functions.h"


PlanetaryBody::PlanetaryBody(vec3 newPosition, vec3 newVelocity, double newMass, std::string newName)
{

	position = newPosition;
	velocity = newVelocity;
	mass = newMass;
	name = newName;
}

void PlanetaryBody::addF(vec3 addForce)
{

	force += addForce;

}

void PlanetaryBody::resetF()
{
	force = 0.;
}

void PlanetaryBody::integrate(double &dt)
{

	velocity += (force/mass) * dt;
	position += velocity * dt;
}
