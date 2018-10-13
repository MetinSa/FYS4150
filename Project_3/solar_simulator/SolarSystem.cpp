#include "functions.h"


SolarSystem::SolarSystem(std::string filename){
	std::ifstream infile(filename);
	std::string line;

	std::vector<std::string> name;
	std::vector<double> rx;
	std::vector<double> ry;
	std::vector<double> rz;
	std::vector<double> vx;
	std::vector<double> vy;
	std::vector<double> vz;
	std::vector<double> m;

	for (int i = 0; i < 8; i++)
	{
		getline(infile, line);
		std::istringstream ss(line);

		if (i == 0)
		{
			extractor(name, ss);
		}
		else if (i == 1)
		{
			extractor(rx, ss);
		}
		else if (i == 2)
		{
			extractor(ry, ss);
		}
		else if (i == 3)
		{
			extractor(rz, ss);
		}
		else if (i == 4)
		{
			extractor(vx, ss);
		}
		else if (i == 5)
		{
			extractor(vy, ss);
		}
		else if (i == 6)
		{
			extractor(vz, ss);
		}
		else if (i == 7)
		{
			extractor(m, ss);
		}
	}
	for (int i = 0; i<name.size(); i++)
	{
		vec3 position(rx[i], ry[i], rz[i]);
		vec3 velocity(vx[i], vy[i], vz[i]);
		planets.push_back(PlanetaryBody(position, velocity, m[i], name[i]));
	}

	for (int i = 0; i < planets.size(); i++)
	{
		for (int j = 0; j < planets.size(); j++)
		{
			//gravityforces.push_back(&planets.at(i), &planets.at(j));
		}
	}
}

void SolarSystem::extractor(std::vector<std::string> &vec, std::istringstream &ss)
{
	std::string item;
	ss >> item;

	while (ss >> item)
	{
		vec.push_back(item);
	}
}
void SolarSystem::extractor(std::vector<double> &vec, std::istringstream &ss)
{
	std::string item;
	double value;
	ss >> item;

	while (ss >> value)
	{
		vec.push_back(value);
	}
}
