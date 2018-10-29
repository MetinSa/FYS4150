#include "Ising.h"
#include <iostream>
#include <fstream>

Ising::Ising(int dimension_of_lattice)
{
	// Initializing system properties
	this->dimension_of_lattice = dimension_of_lattice;

	number_of_spins = dimension_of_lattice*dimension_of_lattice;
	lattice = arma::mat(dimension_of_lattice, dimension_of_lattice);
	expectation_values = arma::vec(5);
	delta_energies = arma::vec(17);


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

void Ising::InitializeLattice(double temperature)
{
	// Initializing the lattice (system) for a given temperature. The expectation values are
	// reseted and initial values are computed. Also make us of a lookup-table for energies 
	// to save computation time.


	this->temperature = temperature;

	// Reseting stuff
	energy = 0;
	magnetization = 0;
	number_of_accepted_states = 0;

	// Precomputing possible energies
	for (int i = -8; i <= 8; i++)
	{
		delta_energies(i+8) = 0;
	}

	for (int i = -8; i <= 8; i += 4)
	{
		delta_energies(i+8) = exp(-i/temperature);
	}

	// Initializing spin directions randomly
	for (int i = 0; i < dimension_of_lattice; i++)
	{
		for (int j = 0; j < dimension_of_lattice; j++)
		{
			double rand_condition = rand() * 1./ RAND_MAX;
			lattice(i,j) = (rand_condition < 0.5) ? 1 : -1;
			magnetization += lattice(i,j);
		}
	}


	// Initializing energies
	for (int i = 0; i < dimension_of_lattice; i++)
	{
		for (int j = 0; j < dimension_of_lattice; j++)
		{
			energy -= lattice(i,j) * (lattice(PBC(i, dimension_of_lattice, -1), j) + 
					  lattice(i, PBC(j, dimension_of_lattice, -1)));
		}
	}
	lattice.print("lattice: ");
	std::cout << "magnetization: " <<magnetization << std::endl;
}


int Ising::PBC(int index, int limit, int offset)
{
	// Periodic boundary conditions, returns the index of the requested neighbour.

	return (index + limit  + offset) % limit;
}


void Ising::Metropolis()
{
	// Metropolis montecarlo method

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
				lattice(rand_x, rand_y) *= -1;
				magnetization += 2 * lattice(rand_x, rand_y);
				energy += delta_e;
				number_of_accepted_states++;

			}
		}

}

double Ising::getEnergy(int x, int y)
{
	double up, down, left, right, spin_mat;

	spin_mat = lattice(x,y);
	up = lattice(x, PBC(y, dimension_of_lattice, 1));
	down = lattice(x, PBC(y, dimension_of_lattice, -1));
	left = lattice(PBC(x, dimension_of_lattice, -1), y);
	right = lattice(PBC(x, dimension_of_lattice, 1), y);

	return 2 * spin_mat * (up + down + left + right);


}










