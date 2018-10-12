#include "functions.h"


Planetary_body::Planetary_body(double *r_, double *v_, double &m_)
{
	for (int i = 0; i<3; i++)
	{
		r[i] = r_[i];
		v[i] = v_[i];
		F[i] = 0;
	}
	m = m_;
}

void Planetary_body::addF(double *aF)
{
	for (int i = 0; i<3; i++)
	{
		F[i] += aF[i];
	}

}

void Planetary_body::resetF()
{
	for (int i = 0; i<3; i++)
	{
		F[i] = 0;
	}
}

void Planetary_body::integrate(double &dt)
{
	//Euler-cromer
	for (int i = 0; i<3; i++)
	{
		v[i] += (F[i]/m) * dt;
		r[i] += v[i] * dt;
	}
}

double Planetary_body::getm()
{
	return m;
}

double* Planetary_body::getr()
{
	return r;
}