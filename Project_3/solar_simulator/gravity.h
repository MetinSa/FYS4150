#ifndef GRAVITY_H
#define GRAVITY_H



// Declaring Gravity class

class Gravity
{
	Planetary_body* alpha;
	Planetary_body* beta;
	double G;
public:
	Gravity(PlanetaryBody *a, PlanetaryBody *b);
	void calcForce();
};

#endif