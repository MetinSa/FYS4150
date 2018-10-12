#ifndef VEC3_H
#define VEC3_H

class vec3
{

//	Class that creates and handles vectors in 3-dimensions.

public:
	double components[3];

	//	Default constructor
	vec3();

	//	Parametrized constructor
	vec3(double x, double y, double z);

	//	Copying a vector
	vec3(vec3 const &copy);

	//	Function that prints the vector
	void print();

	//	Function that returns the length squared of a vector
	double lengthSquared();

	//	Function that returns the length of a vector
	double length();

	//	Function that returns the dot product of two vectors
	double dot(vec3 &other);

	//	Function that returns the cross product of two vectors
	vec3 cross(vec3 &other);

	//	Operator definitons
	vec3 &operator += (const vec3 &other);		//	Componentwise addition with other vector
	vec3 &operator -= (const vec3 &other);		//	Componentwise subtraction with other vector
	vec3 &operator += (const double &other);	//	Componentwise addition with scalar
	vec3 &operator -= (const double &other);	//	Componentwise subtraction with scalar
	vec3 &operator *= (const vec3 &other);		//	Componentwise multiplication with other vector
	vec3 &operator /= (const vec3 &other);		//	Componentwise division with other vector
	vec3 &operator *= (const double &other);	//	Componentwise multiplication with scalar
	vec3 &operator /= (const double &other);	//	Componentwise division with scalar

};

//	Making the coding seem more mathematical
inline vec3 operator+(vec3 lhs, vec3 rhs)
{
	lhs += rhs;
	return lhs;

}

inline vec3 operator-(vec3 lhs, vec3 rhs)
{
	lhs -= rhs;
	return lhs;

}

inline vec3 operator+(vec3 lhs, double rhs)
{
	lhs += rhs;
	return lhs;

}

inline vec3 operator-(vec3 lhs, double rhs)
{
	lhs -= rhs;
	return lhs;

}

inline vec3 operator*(vec3 lhs, vec3 rhs)
{
	lhs *= rhs;
	return lhs;

}

inline vec3 operator/(vec3 lhs, vec3 rhs)
{
	lhs /= rhs;
	return lhs;

}

inline vec3 operator*(vec3 lhs, double rhs)
{
	lhs *= rhs;
	return lhs;

}

inline vec3 operator/(vec3 lhs, double rhs)
{
	lhs /= rhs;
	return lhs;

}

#endif // VEC3_H