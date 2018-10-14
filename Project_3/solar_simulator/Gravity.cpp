#include "functions.h"
#include <ostream>

Gravity::Gravity(PlanetaryBody *a, PlanetaryBody *b)
{
	// Class that computes the Newtonian gravitational force.

	object_a = a;
	object_b = b;

	// Scaled gravitational constant
	G = 4*pi*pi;
}

void Gravity::calculateForce()
{
	// Function that calculates the force between two objects a and b.

	// Defining position and force vectors
	vec3 r_a = object_a->position;
	vec3 r_b = object_b->position;
	vec3 F;

	// Computing the length of position that separates object a and b
	double length = (r_b-r_a).length();
	
	// Computing the Newtonian gravitational force
	F = ((r_b-r_a)/pow(length, 3))*(G * object_a->mass * object_b->mass);

	object_a->addF(F);
	object_b->addF(-F);
}
