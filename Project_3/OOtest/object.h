#ifndef OBJECT_H
#define OBJECT_H

#include "vec3.h"
#include <iostream>
#include <string>

class object
{

	//	Class that initializes a object (planet/moon etc).

public:
	//	Allocating quantities to the object, using the vec3 class
	vec3 position;
	vec3 velocity;
	vec3 force;
	double mass;
	std::string name;

	//	Initializing a new object
	object(vec3 newPosition, vec3 newVelocity, vec3 newForce, double newMass, std::string newName);

	//	Printing information about the Object
	void objPrint();
};

#endif	// OBJECT_H