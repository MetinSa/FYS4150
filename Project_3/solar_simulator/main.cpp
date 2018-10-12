#include "functions.h"


int main(int argc, char *argv[]){
	const int n = 3;		// Number of planetary bodies
	double r[n][3] = {{4.2, 2.3, 3.2}, {-3.1, -4.4, -1.2}, {1.2, 3.3, 2.3}};
	double v[n][3] = {{23.2, 1.3, 32.55}, {3.2, 1.3, 2.55}, {2.0, 0.3, 3.0}};
	double m[n] = {6, 3, 1};
	double dt = .01;
	const double t_end = 1;
	double t = 0;
	
	std::vector<Planetary_body> planets;
	planets.reserve(n);
	std::vector<Gravity> gravity;
	
	// Create planetary bodies
	for (int i = 0; i<n; i++)
	{
		planets.emplace_back(r[i], v[i], m[i]);
	}
	
	// Create gravitational forces
	for (int i = 0; i<n; i++)
	{
		for (int j = i+1; j<n; j++)
		{
			gravity.emplace_back(&planets.at(i), &planets.at(j));
		}
	}
	
	
	while (t < t_end)
	{
		// Calculate forces
		for (int i = 0; i < gravity.size(); i++)
		{
			gravity[i].calcForce();
		}
		
		// Integrate all planetary bodies
		for (int i = 0; i < n; i++)
		{
			planets[i].integrate(dt);
			
			// Print positions
			std::cout << "Body " << i << ":" << std::endl;
			double *r = planets[i].getr();
			for (int j = 0; j <3; j++)
			{
				std::cout << r[j] << " ";
			}
			std::cout << std::endl;
		}
		t += dt;
	}
	
}