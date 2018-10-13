#ifndef GRAVITY_H
#define GRAVITY_H

// Declaring Gravity class

class Gravity
{
	PlanetaryBody* object_a;
	PlanetaryBody* object_b;
	double G;

public:
	// Constructor 
	Gravity(PlanetaryBody *a, PlanetaryBody *b);

	// Function that computes the forces between object a and b.
	void calculateForce();
};

#endif