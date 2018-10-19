#include "functions.h"

SmallObject::SmallObject(vec3 newPosition, vec3 newVelocity, std::string newName, std::vector<PlanetaryBody> * innplanets)
{
	position = newPosition;
	velocity = newVelocity;
	name = newName;

	planets = innplanets;
}

SmallObject::SmallObject(vec3 newPosition, vec3 newVelocity, std::string newName, std::vector<PlanetaryBody> * innplanets, bool isrelativistic)
{
	position = newPosition;
	velocity = newVelocity;
	name = newName;

	planets = innplanets;

	relativistic = isrelativistic;
}

void SmallObject::calcA()
{
	vec3 r_p;
	double length;
	acceleration = 0;

	for (int i = 0; i < planets->size(); i++)
	{
		r_p = planets->at(i).position;
		length = (r_p-position).length();

		if (relativistic)
		{
			acceleration += 0; // Insert relativistic formula here.
		}
		else
		{
			acceleration += ((r_p-position)/pow(length, 3))*(G * planets->at(i).mass);
		}
	}
}

void SmallObject::objPrint()
{
	// Printing information about the object.

	std::cout << "Object: " << name << std::endl;
	std::cout << "Position: ";
	position.print();
	std::cout << "Velocity: ";
	velocity.print();
	std::cout << "Acceleration: ";
	acceleration.print();
}
