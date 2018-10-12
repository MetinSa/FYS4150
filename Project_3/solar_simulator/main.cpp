#include "functions.h"


int main(int argc, char *argv[]){

	vec3 v1(1,2,3);
	vec3 v2(4,2,1);

	double a = (v2-v1).length();

	std::cout << a << std::endl;
	return 0;

	
}