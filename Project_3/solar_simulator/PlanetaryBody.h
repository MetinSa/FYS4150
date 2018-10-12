#ifndef PLANETARYBODY_H
#define PLANETARYBODY_H


// Declaring Planetary_body class

class Planetary_body
{
	double r[3];
	double v[3];
	double F[3];
	double m;

public:
	Planetary_body(double *r_, double *v_, double &m_);
	void addF(double *aF);
	void setr(double *r_);
	void resetF();
	void integrate(double &dt);
	double getm();
	double* getr();
};

#endif
