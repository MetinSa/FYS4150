#include "functions.h"


int main(int argc, char *argv[]){

	double years, dt;
	std::string systemname;

	// Commandline arguments
	if (argc == 2)
	{
		systemname = argv[1];
		years = 10;
		dt = 0.01;
	}
	else if (argc >= 4)
	{
		systemname = argv[1];
		years = atof(argv[2]);
		dt = atof(argv[3]);
	}
	else
	{
		systemname = "planets.txt";
		years = 10;
		dt = 0.01;
	}

	// Setting up the system
	SolarSystem planetary_system(systemname);

	// Integrating the system using desired method
	Solver Integrate(planetary_system);

	// Integrate.forwardEuler(dt, years);
	Integrate.velocityVerlet(dt, years);

	return 0;

}
