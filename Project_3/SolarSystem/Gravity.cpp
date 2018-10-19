#include "functions.h"
#include <ostream>

Gravity::Gravity(PlanetaryBody *a, PlanetaryBody *b)
{
	// Class that computes the Newtonian gravitational force.

	object_a = a;
	object_b = b;

}

Gravity::Gravity(PlanetaryBody *a, PlanetaryBody *b, bool isrelativistic)
{
	object_a = a;
	object_b = b;

	relativistic = isrelativistic;
}

void Gravity::calculateForce()
{
	// Function that calculates the force between two objects a and b.

	// Defining position and force vectors
	vec3 F;
	vec3 r_a = object_a->position;
	vec3 r_b = object_b->position;

	// Computing the length of position that separates object a and b
	double length = (r_b-r_a).length();
	
	// Computing the Newtonian gravitational force
	if (relativistic)
	{
		F = 0; //insert relativistic formula her
	}
	else
	{
		F = ((r_b-r_a)/pow(length, 3))*(G * object_a->mass * object_b->mass);
	}

	// Adding force which can be used when integrating
	object_a->addF(F);
	object_b->addF(-F);
}

double Gravity::PotentialEnergy()
{
	// Returning the potential energy of an object.

	vec3 r_a = object_a->position;
	vec3 r_b = object_b->position;

	// Computing the length of position that separates object a and b
	double length = (r_b-r_a).length();
	return (G*object_a->mass*object_b->mass)/(length);
}
