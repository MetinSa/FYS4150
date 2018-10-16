#include "functions.h"


int main(int argc, char *argv[]){

	// Creating Earth class
  double massEarth = 5.97219e24/solarmass;
  vec3 positionEarth(9.472338196836673e-1, 3.216790877655131e-1, -9.310425816193890e-5);
  vec3 velocityEarth(-5.712595804744874e-3, 1.627120685499318e-2,-3.033942175908446e-7);
  PlanetaryBody earth(positionEarth, velocityEarth, massEarth, "Earth");


  // Creating Sun class
  double massSun = 1.0;
  vec3 positionSun(-1.323134155066396e-4, 7.243723191520690e-3, -7.306026998949559e-5);
  vec3 velocitySun(-7.580700660070726e-6, 2.608579279446222e-6, 1.894756755889952e-7);
  PlanetaryBody sun(positionSun, velocitySun, massSun, "Sun");

  Solver newSystem;
  newSystem.add(earth);
  newSystem.add(sun);
  newSystem.setupForces();

  newSystem.forwardEuler(1e5, 10);




	// double dt = .001;
	// double T_end = 10;
	//
	// SolarSystem sol("planets.txt");
	// sol.integrate(dt, T_end);
	// sol.printobjects();
	// sol.planets[4].objPrint();
	// double l = sol.planets[4].AngularMomentum();
	// double kinetic = sol.planets[4].KineticEnergy();
	// std::cout << kinetic << std::endl;
	/*
	vec3 earthposition(1,0,0);
	vec3 earthvelocity(0,2*pi,0);
	double earthmass = 0.001;

	vec3 solarposition(0,0,0);
	vec3 solarvelocity(0,0,0);
	double solarmass = 1;

	double dt = 0.00001;
	double T_stop = 1;
	double t = 0;

	PlanetaryBody sun(solarposition, solarvelocity, solarmass, "Sun");
	PlanetaryBody earth(earthposition, earthvelocity, earthmass, "Earth");

	Gravity earthpull(&sun, &earth);

	std::string path = "output/";
	std::ofstream outfile(path+"output.txt");
	outfile << earth.position[0] << " " << earth.position[1] << " " << earth.position[2] << std::endl;

	while (t <= T_stop)
	{
		earthpull.calculateForce();
		sun.integrate(dt);
		earth.integrate(dt);
		outfile << earth.position[0] << " " << earth.position[1] << " " << earth.position[2] << std::endl;
		t += dt;
	}
	outfile.close();
	sun.objPrint();
	earth.objPrint();
	*/
	return 0;

}
