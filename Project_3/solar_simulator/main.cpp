#include "functions.h"


int main(int argc, char *argv[]){

	double dt = .001;
	double T_end = 2;

	SolarSystem sol("planets.txt");
	sol.integrate(dt, T_end);
	sol.printobjects();

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
