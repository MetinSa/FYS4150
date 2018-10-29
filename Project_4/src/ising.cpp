#include "Ising.h"
#include <iostream>
#include <fstream>

Ising::Ising(int dimension_of_lattice)
{
	// Initializing system properties
	this->dimension_of_lattice = dimension_of_lattice;

	number_of_spins = dimension_of_lattice*dimension_of_lattice;

	spin_matrix = arma::mat(dimension_of_lattice, dimension_of_lattice);
	expectation_values = arma::vec(1);
	delta_energies = arma::vec(1);


	// Energy
	energy = 0;
	mean_energy = 0;
	energy_variance = 0;
	specific_heat = 0;

	// Magnetization
	magnetization = 0;
	mean_magnetization = 0;
	susceptibility = 0;
	mean_absoloute_magnetization = 0;

};

int Ising::PBC(int index, int limit, int offset)
{

	// Periodic boundary conditions, returns the index of the requested neighbour.

	return (index + limit  + offset) % limit;
}


void Ising::Metropolis()
{

	for (int i = 0; i < number_of_spins; i++)
		{
			// Removing potensial bias
			int rand_x = rand() % dimension_of_lattice;
			int rand_y = rand() % dimension_of_lattice;

			double delta_e = getEnergy(rand_x, rand_y);
			double rand_condition = rand() * 1./ RAND_MAX;

			// Update variables if metropolis condition is met
			if (rand_condition <= delta_energies(delta_e + 8))
			{
				spin_matrix(rand_x, rand_y) *= -1;
				magnetization += 2 * spin_matrix(rand_x, rand_y);
				energy += delta_e;
				number_of_accepted_states++;

			}
		}

}

double Ising::getEnergy(int x, int y)
{
	double up, down, left, right, spin_mat;

	spin_mat = spin_matrix(x,y);
	up = spin_matrix(x, PBC(y, dimension_of_lattice, 1));
	down = spin_matrix(x, PBC(y, dimension_of_lattice, -1));
	left = spin_matrix(PBC(x, dimension_of_lattice, -1), y);
	right = spin_matrix(PBC(x, dimension_of_lattice, 1), y);

	return 2 * spin_mat * (up + down + left + right);


}










