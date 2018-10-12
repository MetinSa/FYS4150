#ifndef PLANETARYBODY_H
#define PLANETARYBODY_H


// Declaring Planetary_body class

class Planetary_body
{
	vec3 position;
	vec3 velocity;
	vec3 force;
	double mass;
	std::string name;

public:
	Planetary_body(vec3 newposition, vec3 newvelocity, vec3 newMass, std::string name);
	void addF(vec3 addForce);
	void resetF();
	void integrate(double &dt);
	double getm();
	vec3 getr();

};

#endif
