#ifndef GRAVITY_H
#define GRAVITY_H



// Declaring Gravity class

class Gravity
{
	Planetary_body* alpha;
	Planetary_body* beta;
	double G;
public:
	Gravity(Planetary_body *a, Planetary_body *b);
	void calcForce();
};

#endif