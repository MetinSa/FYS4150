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

void PlanetaryBody::objPrint()
{

	// Printing information about the object.

	std::cout << "Object: " << name << std::endl;
	std::cout << "Position: ";
	position.print();
	std::cout << "Velocity: ";
	velocity.print();
	std::cout << "Force: ";
	force.print();
	std::cout << "Mass: " << mass << std::endl;
}