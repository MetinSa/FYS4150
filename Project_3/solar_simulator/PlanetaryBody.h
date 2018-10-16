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
	// Adding force to an object
	void addF(vec3 addForce);

	// Resetting the force of an object	
	void resetF();

	// Computing the angular momentum of the object
	double AngularMomentum();

	// Computing the kinetic energy of the object
	double KineticEnergy();

	// Integrating object's velocity and position using the Forward Euler method
	void ForwardEuler(double &dt);	

	// Integrating object's velocity and position using the Velocity Verlet method 
	void VelocityVerlet(double &dt);

	// Printing information about the object
	void objPrint();

};

#endif
