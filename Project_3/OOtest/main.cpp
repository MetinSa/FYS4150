#include <iostream>
#include "vec3.h"
#include "CelestialObject.h"

int main()
{

	CelestialObject earth(vec3(1,0,0), vec3(0,1,0), vec3(0,0,0), 1, "Earth");

	// earth.objPrint();

	vec3 v1(1,2,3);
	// vec3 v2(2,2,2);
	// vec3 v3;
	// v3 = v1.cross(v2);
	// v3.print();
	// double a = v1.dot(v2);
	// std::cout << a << std::endl;
	// v1.print();
	// v2.print();

	double dFx = 2;
	double dFy = 1;
	double dFz = 4;

	// earth.addForce(dFx, dFy, dFz);

	// earth.objPrint();

	// earth.resetForce();

	// earth.objPrint();

	v1.print("v1");

	return 0;
}