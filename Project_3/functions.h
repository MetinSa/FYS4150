#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Gravity
{
	Planetary_body* alpha;
	Planetary_body* beta;
	double G;
public:
	Gravity(Planetary_body* a, Planetary_body* b);
	void calcForce();
};

class Planetary_body
{
	double r[3];
	double v[2];
	double F[2];
	double m;

public:
	Planetary_body(double* r_, double* v_, double* F_, double m_);
	void addF(double* F_);
	void setr(double* r_);
	void resetF();
	void integrate(double);
	double* getr();
};

#endif
