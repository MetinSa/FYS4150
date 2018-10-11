#include "object.h"

object::object(vec3 newPosition, vec3 newVelocity, vec3 newForce, double newMass, std::string newName)
{

	// Initializing a new object and allocating it the below quantities.

	position = newPosition;
	velocity = newVelocity;
	force = newForce;
	mass = newMass;
	name = newName;
}

void object::objPrint()
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
