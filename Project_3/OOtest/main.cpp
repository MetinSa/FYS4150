#include <iostream>
#include "vec3.h"

int main()
{

	vec3 v1(3,4,1);

	vec3 v2(1,2,3);

	vec3 v3;

	double a = 1.5;

	v3 = v1 + a;

	v3.print();
	return 0;
}