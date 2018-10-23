#ifndef GRAVITY_H
#define GRAVITY_H
// Declaring Gravity class

class Gravity
{
	// Initializing vectors and the gravitational constant.

	PlanetaryBody* object_a;
	PlanetaryBody* object_b;

	bool relativistic = false;

public:
	// Constructor 
	Gravity(PlanetaryBody *a, PlanetaryBody *b);
	Gravity(PlanetaryBody *a, PlanetaryBody *b, bool isrelativistic);

	// Function that computes the forces between object a and b.
	void calculateForce();

	// Function that computes the potential energy between object a and b.
	double PotentialEnergy();
};

#endif
