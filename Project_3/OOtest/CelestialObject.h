#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include "vec3.h"
#include <iostream>
#include <string>

class CelestialObject
{

	//	Class that initializes a celestial object (planet/moon etc).

public:
	//	Allocating quantities to the object, using the vec3 class
	vec3 position;
	vec3 velocity;
	vec3 force;
	double mass;
	std::string name;

	//	Initializing a new object
	CelestialObject(vec3 newPosition, vec3 newVelocity, vec3 newForce, double newMass, std::string newName);

	//	Printing information about the ibject
	void objPrint();

	//	Adding force to an object
	void addForce(double dFx, double dFy, double dFz);

	//	Resetting the force of an object
	void resetForce();
};

#endif	// CELESTIALOBJECT_H