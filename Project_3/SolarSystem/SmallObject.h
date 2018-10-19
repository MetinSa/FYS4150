#ifndef SMALLOBJECT_H_
#define SMALLOBJECT_H_

class SmallObject
{
public:
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	std::string name;
	std::vector<PlanetaryBody> * planets;
	double G;

	SmallObject(vec3 newPosition, vec3 newVelocity, std::string newName, std::vector<PlanetaryBody> * innplanets);

	// Calculate total acceleration to an object
	void calcA();

	// Printing information about the object
	void objPrint();

};



#endif
