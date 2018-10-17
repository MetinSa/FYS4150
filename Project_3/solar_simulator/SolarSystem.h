#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

class SolarSystem
{
	// Class that creates the Solar system

public:

	// Initializing vectors
	std::vector<PlanetaryBody> smallobjects;
	std::vector<PlanetaryBody> objects;
	std::vector<Gravity> gravityForces;

	// Read and write to file functions
	void extractor(std::vector<std::string> &vec, std::istringstream &ss);
	void extractor(std::vector<double> &vec, std::istringstream &ss);
	void dumptofile();
	void writeheader();

	// Constructor
	SolarSystem(std::string filename);

	// Integration function
	void integrate(double dt, double T_stop);

	// print planetary information function
	void printobjects();
};

#endif
