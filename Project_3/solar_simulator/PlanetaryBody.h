#ifndef PLANETARYBODY_H
#define PLANETARYBODY_H


// Declaring Planetary_body class

class PlanetaryBody
{
public:
	vec3 position;
	vec3 velocity;
	vec3 force;
	double mass;
	std::string name;
	PlanetaryBody(vec3 newPosition, vec3 newVelocity, double newMass, std::string name);
	void addF(vec3 addForce);
	void resetF();
	void integrate(double &dt);

};

#endif
