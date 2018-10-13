#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

// Declaring Gravity class

class SolarSystem
{
	std::vector<PlanetaryBody> planets;
	std::vector<Gravity> gravityforces;

	void extractor(std::vector<std::string> &vec, std::istringstream &ss);
	void extractor(std::vector<double> &vec, std::istringstream &ss);
public:
	// Constructor
	SolarSystem(std::string filename);


};

#endif
