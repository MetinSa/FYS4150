#ifndef PLANETARYBODY_H
#define PLANETARYBODY_H


// Declaring PlanetaryBody class.

class PlanetaryBody
{

public:

	// Properties of the object
	vec3 position;
	vec3 velocity;
	vec3 force;
	double mass;
	std::string name;

	// Constructor	
	PlanetaryBody(vec3 newPosition, vec3 newVelocity, double newMass, std::string name);
	
	//	Adding force to an object
	void addF(vec3 addForce);

	//	Resetting the force of an object	
	void resetF();

	// Integrating object's velocity and position using the Forward Euler method
	void integrate(double &dt);

	//	Printing information about the object
	void objPrint();

};

#endif
