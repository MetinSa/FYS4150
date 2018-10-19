#include "functions.h"


int main(int argc, char *argv[]){

	double years, dt;

	// Commandline arguments
	std::string systemname = argv[1];
	years = atof(argv[2]);
	dt = atof(argv[3]);

	// Setting up the system
	SolarSystem planetary_system(systemname);

	// Integrating the system using desired method
	Solver Integrate(planetary_system);

	// Integrate.forwardEuler(dt, years);
	Integrate.velocityVerlet(dt, years);

	return 0;

}
