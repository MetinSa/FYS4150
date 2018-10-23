#include "functions.h"


SolarSystem::SolarSystem(std::string filename)
{
	// Class that creates a system by reading in given planetary bodies.

	name = filename;
	filereader(false);
	CreateGravity(false);

}

SolarSystem::SolarSystem(std::string filename, std::vector<PlanetaryBody> objects_)
{
	// Class that creates a system by reading in given planetary bodies.
	name = filename;
	objects = objects_;
	CreateGravity(false);
}

SolarSystem::SolarSystem(std::string filename, std::vector<PlanetaryBody> objects_, bool relativistic)
{
	// Class that creates a system by reading in given planetary bodies.
	name = filename;
	objects = objects_;
	CreateGravity(relativistic);
}

SolarSystem::SolarSystem(std::string filename, bool isrelativistic)
{
	// Class that creates a system by reading in given planetary bodies.

	// Reading in planetary information from file
	name = filename;
	filereader(isrelativistic);
	CreateGravity(isrelativistic);

}

void SolarSystem::filereader(bool isrelativistic)
{
	// Reading in planetary information from file
	std::ifstream infile("PlanetarySystems/" + name);
	std::string line;

	std::vector<std::string> names;
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

		if (i == 0){extractor(names, ss);}
		else if (i == 1){extractor(rx, ss);}
		else if (i == 2){extractor(ry, ss);}
		else if (i == 3){extractor(rz, ss);}
		else if (i == 4){extractor(vx, ss);}
		else if (i == 5){extractor(vy, ss);}
		else if (i == 6){extractor(vz, ss);}
		else if (i == 7){extractor(m, ss);}
	}

	// Creating objects for all given objects
	for (int i = 0; i<names.size(); i++)
	{
		vec3 position(rx[i], ry[i], rz[i]);
		vec3 velocity(vx[i], vy[i], vz[i]);
		if (m[i] == 0)
		{
			smallobjects.push_back(SmallObject(position, velocity, names[i], &objects, isrelativistic));
		}
		else
		{
			objects.push_back(PlanetaryBody(position, velocity, m[i], names[i]));
		}
	}
}

void SolarSystem::CreateGravity(bool relativistic)
{
	// Computing the gravitational forces between all major objects
	for (int i = 0; i < objects.size()-1; i++)
	{
		for (int j = i+1; j < objects.size(); j++)
		{
			gravityForces.push_back(Gravity(&objects.at(i), &objects.at(j), relativistic));
		}
	}
}

void SolarSystem::CreateSmallObject(vec3 newPosition, vec3 newVelocity, std::string newName, bool isrelativistic)
{
	smallobjects.push_back(SmallObject(newPosition, newVelocity, newName, &objects, isrelativistic));
}

void SolarSystem::extractor(std::vector<std::string> &vec, std::istringstream &ss)
{

	// Function that extracts items from file (string)

	std::string item;
	ss >> item;

	while (ss >> item)
	{
		vec.push_back(item);
	}
}
void SolarSystem::extractor(std::vector<double> &vec, std::istringstream &ss)
{

	// Function that extracts items from file (vector)

	std::string item;
	double value;
	ss >> item;

	while (ss >> value)
	{
		vec.push_back(value);
	}
}



void SolarSystem::dumptofile(double t)
{

	// Writing the position of the objects to file instead of saving the information in arrays

	std::string path = "output/";
	std::ofstream outfile;
	outfile.open(path+name, std::ios_base::app);
	outfile << t << " ";

	for (int i = 0; i < objects.size(); i++)
	{
		outfile <<  objects[i].position[0] << " " << objects[i].position[1] << " " << objects[i].position[2] << " ";
	}
	for (int i = 0; i < smallobjects.size(); i++)
	{
		outfile <<  smallobjects[i].position[0] << " " << smallobjects[i].position[1] << " " << smallobjects[i].position[2] << " ";
	}
	outfile << std::endl;

}

void SolarSystem::dumpenergytofile()
{
	double Ek;
	double Ep;

	std::string path = "output/";
	std::string energystring = "energy";
	std::ofstream outfile;
	outfile.open(path+energystring+name, std::ios_base::app);

	for (int i = 0; i < objects.size(); i++){
		Ek += objects[i].KineticEnergy();
	}

	for (int i = 0; i < gravityForces.size(); i++){
    Ep -= gravityForces[i].PotentialEnergy();
  }

	// for (int i = 0; i < smallobjects.size(); i++){
	// 	Ek += smallobjects[i].KineticEnergy();
	// }


	outfile <<  Ek << " " << Ep << " ";
	outfile << std::endl;

	Ek = 0;
	Ep = 0;

}

void SolarSystem::writeheader()
{

	// Writing a header with the name of the objects
	std::string path = "output/";

	std::ofstream outfile(path+name);

	outfile << "time" << " ";

	for (int i = 0; i < objects.size(); i++)
	{
		outfile << objects[i].name << "||" << objects[i].mass << " ";
	}
	for (int i = 0; i < smallobjects.size(); i++)
	{
		outfile << smallobjects[i].name << "||" << 0 << " ";
	}
	outfile << std::endl;

}

void SolarSystem::writeenergyheader()
{

	// Writing a header with the name of the objects
	std::string path = "output/";
  std::string energystring = "energy";

	std::ofstream outfile(path+energystring+name);
}


void SolarSystem::printobjects()
{

	// Using the objPrint() function to print all relevant information about all objects

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].objPrint();
		std::cout << std::endl;
	}
	for (int i = 0; i < smallobjects.size(); i++)
	{
		smallobjects[i].objPrint();
		std::cout << std::endl;
	}
}
