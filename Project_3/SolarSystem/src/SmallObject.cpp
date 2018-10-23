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
		vec3 a;
		r_p = planets->at(i).position;
		length = (r_p-position).length();

		a = ((r_p-position)/pow(length, 3))*(G * planets->at(i).mass);

		if (relativistic)
		{
			acceleration += a*(1+3*pow(AngularMomentum(),2)/(position.dot(position)*c*c));
		}
		else;
		{
			acceleration += a;
		}

	}
}

double SmallObject::AngularMomentum()
{
	// Returning the angular momentum per mass of an object.

	return position.cross(velocity).length();
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
