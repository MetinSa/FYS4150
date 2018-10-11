#include "vec3.h"
#include <iostream>

vec3::vec3()
{

	//	Constructs a zero vector.

	components[0] = 0;
	components[1] = 0;
	components[2] = 0;
}

vec3::vec3(double x, double y, double z)
{

	// Allocates x, y and z components to the vector.

	components[0] = x;
	components[1] = y;
	components[2] = z;
}

void vec3::print()
{

	//	Prints the contents of the given vector.

	std::cout << "[" << components[0] << ", " << components[1] << ", " << components[2] << "]" << std::endl;
}

vec3 &vec3::operator+=(const vec3 &other)
{

	//	Vector-vector componentwise addition.

	components[0] += other.components[0];
	components[1] += other.components[1];
	components[2] += other.components[2];
	return *this;
}

vec3 &vec3::operator-=(const vec3 &other)
{

	//	Vector-vector componentwise subtraction.

	components[0] -= other.components[0];
	components[1] -= other.components[1];
	components[2] -= other.components[2];
	return *this;
}

vec3 &vec3::operator+=(const double &other)
{

	//	Vector-scalar componentwise addition.

	components[0] += other;
	components[1] += other;
	components[2] += other;
	return *this;
}

vec3 &vec3::operator-=(const double &other)
{

	//	Vector-scalar componentwise subtraction.

	components[0] -= other;
	components[1] -= other;
	components[2] -= other;
	return *this;
}

vec3 &vec3::operator*=(const vec3 &other)
{

	//	Vector-vector componentwise multiplication.

	components[0] *= other.components[0];
	components[1] *= other.components[1];
	components[2] *= other.components[2];
	return *this;
}

vec3 &vec3::operator/=(const vec3 &other)
{

	//	Vector-vector componentwise division.

	components[0] /= other.components[0];
	components[1] /= other.components[1];
	components[2] /= other.components[2];
	return *this;
}

vec3 &vec3::operator*=(const double &other)
{

	//	Vector-scalar componentwise multiplication.

	components[0] *= other;
	components[1] *= other;
	components[2] *= other;
	return *this;
}

vec3 &vec3::operator/=(const double &other)
{

	//	Vector-scalar componentwise division.

	components[0] /= other;
	components[1] /= other;
	components[2] /= other;
	return *this;
}

