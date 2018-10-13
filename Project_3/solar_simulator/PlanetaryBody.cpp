#include "functions.h"


PlanetaryBody::PlanetaryBody(vec3 newPosition, vec3 newVelocity, double newMass, std::string newName)
{
	// Initializing an object (planet, star, moon etc).

	position = newPosition;
	velocity = newVelocity;
	mass = newMass;
	name = newName;
}

void PlanetaryBody::addF(vec3 addForce)
{
	// Adding force to an object.

	force += addForce;
}

void PlanetaryBody::resetF()
{
	// Reseting the force of an object.

	force = 0;
}

void PlanetaryBody::integrate(double &dt)
{
	// Integrating using the Forward Euler method.

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