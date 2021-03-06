#include "Ising.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <random>

Ising::Ising(int dimension_of_lattice, std::string filename)
{
	// The constructor. 
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

void Ising::InitializeLattice(double temperature, bool oriented_lattice)
{
	// Initializing the lattice (system) for a given temperature. The expectation values are
	// reseted and initial values are computed. Also makes use of a lookup-table for energies 
	// to save computation time.

	this->temperature = temperature;

	// Reseting stuff for reusablility
	energy = 0;
	magnetization = 0;
	number_of_accepted_states = 0;
	expectation_values.zeros();

	// Precomputing possible initial energies for a given temperature
	for (int i = -8; i <= 8; i++)
	{
		energy_difference(i+8) = 0;
	}

	for (int i = -8; i <= 8; i += 4)
	{
		energy_difference(i+8) = exp(-i/temperature);
	}

	// Initialzing seed and the Mersienne random generator
	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::uniform_real_distribution<double> RNG(0.0, 1.0);

	// Initializing spin directions randomly
	for (int i = 0; i < dimension_of_lattice; i++)
	{
		for (int j = 0; j < dimension_of_lattice; j++)
		{
			if (oriented_lattice == true)
			{
				lattice(i,j) = 1;
			}

			else
			{
				double rand_condition = RNG(generator);
				lattice(i,j) = (rand_condition < 0.5) ? 1 : -1;
			}
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
}


void Ising::MonteCarloSample(int number_of_mc_cycles, bool intermediate_calculation, int print_every)
{
	// Starts the Monte-Carlo sampling of the Ising-model for N mc-cycles using
	// the Metropolis algorithm.

	// Starts the Monte-Carlo sampling
	for (int i = 0; i < number_of_mc_cycles; i++)
	{
		// Running the Metropolis algorithm
		Metropolis();

		// Updating the expectation values
		expectation_values(0) += energy;
		expectation_values(1) += energy * energy;
		expectation_values(2) += magnetization;
		expectation_values(3) += magnetization * magnetization;
		expectation_values(4) += fabs(magnetization);

		// Toggle on and off intermediate calculations are desired and pass along how often they should be done through print_every
		if ((intermediate_calculation == true) && (i % print_every == 0) && i != 0) 
		{
			// Computes the physical quantities and writes to file
			ComputeQuantities(i);
			WriteToFile(i);
		}
	}
	// Computes the physical quantities of interest
	ComputeQuantities(number_of_mc_cycles);
}


void Ising::ComputeQuantities(int current_cycle)
{
	// Functions that calculates physical quantities of interest from the current
	// expectation values.

	// Normalizing the expectation values
	double norm = 1 / ((double) current_cycle);
	arma::vec normalized_expectation_values = expectation_values*norm;
	
	// Variance calculations per spin
	energy_variance = (normalized_expectation_values(1) - normalized_expectation_values(0)*normalized_expectation_values(0)) / number_of_spins;
	susceptibility = (normalized_expectation_values(3) - normalized_expectation_values(2)*normalized_expectation_values(2)) / (number_of_spins * temperature);

	// Physical quantities per spin
	mean_energy = normalized_expectation_values(0) / number_of_spins;
	mean_energy_squared = normalized_expectation_values(1) / number_of_spins;
	mean_magnetization = normalized_expectation_values(2) / number_of_spins;
	specific_heat = energy_variance / (temperature*temperature);
	mean_absolute_magnetization = normalized_expectation_values(4) / number_of_spins;
}


void Ising::Metropolis()
{
	// The Metropolis algorithm.
	for (int i = 0; i < number_of_spins; i++)
		{
			// Using the RNG to extract random indicies for the lattice
			int rand_x = RNG(generator)*dimension_of_lattice;
			int rand_y = RNG(generator)*dimension_of_lattice;

			// Computing the energy difference between a spin and its neighbour at a random lattice location
			double delta_e = getEnergy(rand_x, rand_y);
			double rand_condition = RNG(generator);

			// Comparing the energy difference with a random number which is the Metropolis condition
			// If this condition is met, we accept the state and update the lattice
			if (rand_condition <= energy_difference(delta_e + 8))
			{
				// flipping the spin
				lattice(rand_x, rand_y) *= -1;

				// updating magnetization and energy
				magnetization += 2 * lattice(rand_x, rand_y);
				energy += delta_e;

				// updating the number of accepted states
				number_of_accepted_states++;
			}
		}
}


double Ising::getEnergy(int x, int y)
{
	// Returning the energy difference between a lattice point and its neighbours.

	double spin_matrix = lattice(x,y);
	double up = lattice(x, PBC(y, dimension_of_lattice, 1));
	double down = lattice(x, PBC(y, dimension_of_lattice, -1));
	double left = lattice(PBC(x, dimension_of_lattice, -1), y);
	double right = lattice(PBC(x, dimension_of_lattice, 1), y);

	return 2 * spin_matrix * (up + down + left + right);
}


int Ising::PBC(int index, int limit, int offset)
{
	// Periodic boundary conditions, returns the index of the requested neighbour.

	return (index + limit  + offset) % limit;
}


void Ising::WriteToFile(int current_cycle)
{
	// Writing the results to file
	using namespace std;

	ofstream ofile;
	ofile.open("data/" + filename + ".dat", ios::app);
	ofile << setiosflags(ios::showpoint | ios::uppercase);
	ofile << setprecision(8) << current_cycle;
	ofile << setw(15) << setprecision(8) << temperature;
	ofile << setw(15) << setprecision(8) << mean_energy;
	ofile << setw(15) << setprecision(8) << mean_magnetization;
	ofile << setw(15) << setprecision(8) << specific_heat;
	ofile << setw(15) << setprecision(8) << susceptibility;
	ofile << setw(15) << setprecision(8) << mean_absolute_magnetization;
	ofile << setw(15) << setprecision(8) << number_of_accepted_states << "\n";
	ofile.close();

}

void Ising::MPIWriteToFile(int number_of_experiments, double T[] ,double E[], double EE[], double EV[], double CV[],
							 double M[], double absM[], double sus[], double acc_states[])
{
	// Writing the results from the parallel calculation to file
	using namespace std;

	ofstream ofile;
	ofile.open("data/" + filename + ".dat", ios::app);
	ofile << setiosflags(ios::showpoint | ios::uppercase);	
	for (int i = 0; i < number_of_experiments; i++)
	{
		ofile << setw(15) << setprecision(8) << T[i];
		ofile << setw(15) << setprecision(8) << E[i];
		ofile << setw(15) << setprecision(8) << EE[i];
		ofile << setw(15) << setprecision(8) << EV[i];
		ofile << setw(15) << setprecision(8) << CV[i];
		ofile << setw(15) << setprecision(8) << M[i];
		ofile << setw(15) << setprecision(8) << absM[i];
		ofile << setw(15) << setprecision(8) << sus[i];
		ofile << setw(15) << setprecision(8) << acc_states[i] << "\n";
	}
	ofile.close();
}


void Ising::PrintInfo()
{
	// Printing key information about a mc-sample to the terminal.
    using namespace std;

    cout << "===========================================" << endl
    	 << "Monte Carlo Simulation for N: " << number_of_mc_cycles << " cycles." << endl
    	 << "===========================================" << endl
    	 << "Temperature: " << temperature << endl
    	 << "Expected energy: " << mean_energy << endl
    	 << "Expected magnetization: " << mean_magnetization << endl
    	 << "Specific heat: " << specific_heat << endl
    	 << "Energy Variance: " << energy_variance << endl
    	 << "Susceptibility: " << susceptibility << endl
    	 << "Expected absolute magnetization: " << mean_absolute_magnetization << endl
		 << "Number of accepted states per cycle: " << number_of_accepted_states / (double) number_of_mc_cycles << endl
		 << "===========================================" << endl;
}