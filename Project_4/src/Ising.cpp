#include "Ising.h"
#include <iostream>
#include <iomanip>
#include <fstream>

Ising::Ising(int dimension_of_lattice, std::string filename)
{
	// Initializing system properties
	this->dimension_of_lattice = dimension_of_lattice;
	this->filename = filename;

	number_of_spins = dimension_of_lattice*dimension_of_lattice;
	lattice = arma::mat(dimension_of_lattice, dimension_of_lattice);
	expectation_values = arma::vec(5);
	energy_difference = arma::vec(17);


	// Energy
	energy = 0;
	mean_energy = 0;
	energy_variance = 0;
	specific_heat = 0;

	// Magnetization
	magnetization = 0;
	mean_magnetization = 0;
	susceptibility = 0;
	mean_absolute_magnetization = 0;

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
		energy_difference(i+8) = 0;
	}

	for (int i = -8; i <= 8; i += 4)
	{
		energy_difference(i+8) = exp(-i/temperature);
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

	// lattice.print("lattice: ");
	// std::cout << "magnetization: " <<magnetization << std::endl;
}

void Ising::MonteCarloSample(int N)
{
	// Starts the Monte Carlo samping of the Ising-model for N mc-cycles.

	number_of_mc_cycles = N;

	for (int i = 0; i < N; i++)
	{
		Metropolis();
		expectation_values(0) += energy;
		expectation_values(1) += energy * energy;
		expectation_values(2) += magnetization;
		expectation_values(3) += magnetization * magnetization;
		expectation_values(4) += fabs(magnetization);
	}

	// normalizing the expectation values
	double norm = 1 / ((double) N);
	expectation_values *= norm;
	
	// Variance calculations
	energy_variance = (expectation_values(1) - expectation_values(0)*expectation_values(0)) / number_of_spins;
	susceptibility = (expectation_values(3) - expectation_values(2)*expectation_values(2)) / (number_of_spins * temperature);

	// Physical quantities
	mean_energy = expectation_values(0) / number_of_spins;
	mean_magnetization = expectation_values(2) / number_of_spins;
	specific_heat = energy_variance / (temperature*temperature);
	mean_absolute_magnetization = expectation_values(4) / number_of_spins;

	// std::cout << mean_energy << std::endl
	// << susceptibility << std::endl << specific_heat << std::endl <<  mean_absolute_magnetization << std::endl;
}

void Ising::Metropolis()
{
	// Metropolis method

	for (int i = 0; i < number_of_spins; i++)
		{
			// Removing potensial bias
			int rand_x = rand() % dimension_of_lattice;
			int rand_y = rand() % dimension_of_lattice;

			double delta_e = getEnergy(rand_x, rand_y);
			double rand_condition = rand() * 1./ RAND_MAX;

			// Update variables if metropolis condition is met
			if (rand_condition <= energy_difference(delta_e + 8))
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


int Ising::PBC(int index, int limit, int offset)
{
	// Periodic boundary conditions, returns the index of the requested neighbour.

	return (index + limit  + offset) % limit;
}

void Ising::WriteToFile()
{
	using namespace std;

	ofstream ofile;
	ofile.open(filename, ios::app);
	ofile << setiosflags(ios::showpoint | ios::uppercase);

	ofile << setw(20) << setprecision(8) << temperature;
	ofile << setw(20) << setprecision(8) << mean_energy;
	ofile << setw(20) << setprecision(8) << mean_magnetization;
	ofile << setw(20) << setprecision(8) << specific_heat;
	ofile << setw(20) << setprecision(8) << susceptibility;
	ofile << setw(20) << setprecision(8) << mean_absolute_magnetization;
	ofile << setw(20) << setprecision(8) << number_of_accepted_states / (double) number_of_mc_cycles << endl;
	ofile.close();

}

void Ising::PrintInfo(int N)
{
	// Printing key information about a mc-sample to the terminal.
    using namespace std;

    cout << setw(20) << "===========================================" << endl
    	 << "Monte Carlo Simulation for N: " << N << " cycles." << endl
    	 << "===========================================" << endl
    	 << "Temperature: " << temperature << endl
    	 << "Expected energy: " << mean_energy << endl
    	 << "Expected magnetization: " << mean_magnetization << endl
    	 << "Specific heat: " << specific_heat << endl
    	 << "Susceptibility: " << susceptibility << endl
    	 << "Expected absolute magnetization: " << mean_absolute_magnetization << endl
		 << "Number of accepted states per cycle: " << number_of_accepted_states / (double) number_of_mc_cycles << endl
		 << "===========================================" << endl;
}







