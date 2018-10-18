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

double PlanetaryBody::AngularMomentum()
{
	// Returning the angular momentum of an object.

	vec3 rv = position.cross(velocity);
	return mass*rv.length();
}

double PlanetaryBody::KineticEnergy()
{
	// Returning the kinetic energy of an object.
	return (1./2)*mass*velocity.dot(velocity);
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
