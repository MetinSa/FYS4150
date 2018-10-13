#include "functions.h"


int main(int argc, char *argv[]){

	vec3 v1(1,1,1);
	vec3 v2(4,2,-5);
	vec3 v3(-10,-1,2);

	double a = 6.3;
	v1 =  a*v1;
	// v2 = - v2;
	// v3 = - v3;
	v1.print("v1");
	// v2.print("v2");
	// v3.print("v3");

	// double len = v1.length();

	// std::cout << len*len*len << std::endl;

	// PlanetaryBody metian(vec3(1,0,0),vec3(0,1,0),0.3,"Metian");

	// metian.objPrint();

	// vec3 addForce(1,1,1);

	// metian.addF(addForce);

	// metian.objPrint();

	// metian.resetF();

	// metian.objPrint();
	return 0;

}