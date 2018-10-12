#include "functions.h"


int main(int argc, char *argv[]){


	vec3 v1(1,2,3);
	vec3 v2(4,2,1);
	vec3 v3;
	v3 = -v2;
	// double a = -v2.components[0];
	// std::cout << a << std::endl;
	v3.print();
	return 0;

}