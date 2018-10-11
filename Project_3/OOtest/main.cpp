#include <iostream>
#include "vec3.h"
#include "object.h"

int main()
{

	object earth(vec3(1,0,0), vec3(0,1,0), vec3(0,0,0), 1, "Earth");
	earth.objPrint();
	return 0;
}