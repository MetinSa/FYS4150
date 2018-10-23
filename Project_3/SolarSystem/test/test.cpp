#include "functions.h"

int main(int argc, char *argv[]){
	vec3 r;
	vec3 v;
	std::vector<PlanetaryBody> objects;
	objects.push_back(PlanetaryBody(r, v, 1, "Sun"));
	SolarSystem sol("RelativisticMercury.txt", objects, true);

	r[0] = 0.3075;
	v[1] = 12.44;
	sol.CreateSmallObject(r, v, "Mercury", true);

	Solver solve(sol);
	solve.velocityVerlet(0.00001, 0.5);

	return 0;
}
