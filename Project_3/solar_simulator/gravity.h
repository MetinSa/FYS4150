#ifndef GRAVITY_H
#define GRAVITY_H



// Declaring Gravity class

class Gravity
{
	PlanetaryBody* alpha;
	PlanetaryBody* beta;
	double G;
public:
	Gravity(PlanetaryBody *a, PlanetaryBody *b);
	void calcForce();
};

#endif