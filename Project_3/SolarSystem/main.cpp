#include "functions.h"


int main(int argc, char *argv[]){


	//SolarSystem sol("SunEarthSystem.txt");
	//SolarSystem sol("SunEarthJupiterSystem.txt");
	SolarSystem sol("planets.txt");
	Solver solve(sol);
	solve.velocityVerlet(0.01, 5);
	// solve.forwardEuler(0.01, 5);

	return 0;

}
