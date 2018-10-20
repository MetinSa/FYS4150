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
	vec3 r = object_b->position - object_a->position;

	// Computing the length of position that separates object a and b
	double length = r.length();

	// Computing the Newtonian gravitational force
	F = (r/pow(length, 3))*(G * object_a->mass * object_b->mass);

	// Adding force which can be used when integrating
	if (relativistic)
	{
		object_a->addF( F*(1+3*pow(object_a->AngularMomentum(),2)/(r.dot(r)*c*c)));
		object_b->addF(-F*(1+3*pow(object_b->AngularMomentum(),2)/(r.dot(r)*c*c)));
	}
	else
	{
		object_a->addF(F);
		object_b->addF(-F);
	}
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
