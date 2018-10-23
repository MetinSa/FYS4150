#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

class SolarSystem
{
	// Class that creates the Solar system

public:
	// Name of system
	std::string name;

	// Initializing vectors
	std::vector<SmallObject> smallobjects;
	std::vector<PlanetaryBody> objects;
	std::vector<Gravity> gravityForces;

	// Read and write to file functions
	void extractor(std::vector<std::string> &vec, std::istringstream &ss);
	void extractor(std::vector<double> &vec, std::istringstream &ss);
	void dumptofile(std::ofstream &outfile, double t);
	void dumpenergytofile();
	void writeheader(std::ofstream &outfile);
	void writeenergyheader();
	void filereader(bool isrelativistic);

	// Constructor
	SolarSystem(std::string filename);
	SolarSystem(std::string filename, bool relativistic);
	SolarSystem(std::string filename, std::vector<PlanetaryBody> objects_);
	SolarSystem(std::string filename, std::vector<PlanetaryBody>, bool relativistic);

	void CreateGravity(bool relativistic);

	void CreateSmallObject(vec3 newPosition, vec3 newVelocity, std::string newName, bool isrelativistic);

	// print planetary information function
	void printobjects();
};

#endif
