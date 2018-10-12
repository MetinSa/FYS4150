#include "CelestialObject.h"

CelestialObject::CelestialObject(vec3 newPosition, vec3 newVelocity, vec3 newForce, double newMass, std::string newName)
{

	// Initializing a new object and allocating it the below quantities.

	position = newPosition;
	velocity = newVelocity;
	force = newForce;
	mass = newMass;
	name = newName;
}

void CelestialObject::objPrint()
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

void CelestialObject::addForce(double dFx, double dFy, double dFz)
{

	//	Adding force to an object.

	force.components[0] += dFx;
	force.components[1] += dFy;
	force.components[2] += dFz;
}

void CelestialObject::resetForce()
{

	//	Resetting the force for an object.

	force.components[0] = 0;
	force.components[1] = 0;
	force.components[2] = 0;
}
