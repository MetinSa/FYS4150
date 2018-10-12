#include "vec3.h"
#include <iostream>
#include <cmath>

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

vec3::vec3(vec3 const &copy)
{

	//	Copies a vector vec3.

	components[0] = copy.components[0];
	components[1] = copy.components[1];
	components[2] = copy.components[2];
}


void vec3::print()
{

	//	Prints the contents of the given vector.

	std::cout << "[" << components[0] << ", " << components[1] << ", " << components[2] << "]" << std::endl;
}

double vec3::lengthSquared()
{

	//	Returning the length squared of a vector.

	return components[0]*components[0] + components[1]*components[1] + components[2]*components[2];

}

double vec3::length()
{

	//	Returning the length squared of a vector.

	return sqrt(lengthSquared());

}

double vec3::dot(vec3 &other)
{
	//	Returning the dot product of two vectors.

	return components[0]*other.components[0] + components[1]*other.components[1] + components[2]*other.components[2];
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

