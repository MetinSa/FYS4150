#include "functions.h"


SolarSystem::SolarSystem(std::string filename)
{
	// Class that creates a system by reading in given planetary bodies.

	// Reading in planetary information from file
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

		if (i == 0){extractor(name, ss);}
		else if (i == 1){extractor(rx, ss);}
		else if (i == 2){extractor(ry, ss);}
		else if (i == 3){extractor(rz, ss);}
		else if (i == 4){extractor(vx, ss);}
		else if (i == 5){extractor(vy, ss);}
		else if (i == 6){extractor(vz, ss);}
		else if (i == 7){extractor(m, ss);}
	}
	for (int i = 0; i<name.size(); i++)
	{
		vec3 position(rx[i], ry[i], rz[i]);
		vec3 velocity(vx[i], vy[i], vz[i]);
		planets.push_back(PlanetaryBody(position, velocity, m[i], name[i]));
	}

	for (int i = 0; i < planets.size()-1; i++)
	{
		for (int j = i+1; j < planets.size(); j++)
		{
			gravityforces.push_back(Gravity(&planets.at(i), &planets.at(j)));
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

void SolarSystem::integrate(double dt, double T_stop)
{
	double t = 0;
	writeheader();
	dumptofile();
	while (t <= T_stop)
	{
		for (int i = 1; i < gravityforces.size(); i++)
		{
			gravityforces[i].calculateForce();
		}
		for (int i = 1; i < planets.size(); i++)
		{
			planets[i].integrate(dt);
		}

		dumptofile();
		t += dt;
	}
}

void SolarSystem::dumptofile()
{
	std::string path = "output/";
	std::ofstream outfile;
	outfile.open(path+"output.txt", std::ios_base::app);

	for (int i = 0; i < planets.size(); i++)
	{
		outfile << planets[i].position[0] << " " << planets[i].position[1] << " " << planets[i].position[2] << " ";
	}
	outfile << std::endl;

}

void SolarSystem::writeheader()
{
	std::string path = "output/";

	std::ofstream outfile(path+"output.txt");
	for (int i = 0; i < planets.size(); i++)
	{
		outfile << planets[i].name << " ";
	}
	outfile << std::endl;

}

void SolarSystem::printobjects()
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].objPrint();
	}
}
