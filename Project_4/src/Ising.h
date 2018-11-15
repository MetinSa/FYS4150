#include <armadillo>
#include <string>

class Ising
{
	// Class that simulates the two-dimensional Ising model. We use the
	// coupling constant J = 1, and Boltzmann constant k_B = 1, so that
	// temperature has dimension energy. The model is simulated using the
	// Metropolis algorithm with periodic boundary conditions.

public:

	//  =================
	//  System properties
	//  =================

	int dimension_of_lattice;
	int number_of_spins;
	int number_of_mc_cycles;
	int number_of_accepted_states;
	double temperature;

	// On and off functions
	bool oriented_lattice;
	bool intermediate_calculations;
	bool equilibriate;

	arma::mat lattice;
	arma::vec expectation_values;
	arma::vec energy_difference;

	std::string filename;

	//  ======================
	//  Quantities of interest
	//  ======================

	// Energy
	double energy;
	double mean_energy;
	double mean_energy_squared;
	double energy_variance;
	double specific_heat;

	// Magnetization
	double magnetization;
	double mean_magnetization;
	double susceptibility;
	double mean_absolute_magnetization;

	// RandomNumberGenerator
	std::mt19937 generator;
	std::uniform_real_distribution<double> RNG;

	//  ==============
	//  Public Methods
	//  ==============

	// Constructor
	Ising(int dimension_of_lattice, std::string filename);

	// Initiallizing the system
	void InitializeLattice(double temperature, bool oriented_lattice);

	// Monte Carlo integration
	void MonteCarloSample(int number_of_mc_cycles, bool intermediate_calculations, int print_every);

	// The metropolis algorithm
	void Metropolis();

	// Extracting energy
	double getEnergy(int x, int y);

	// Periodic boundary conditions index
	int PBC(int index, int limit, int offset);

	// Computes physical quantities of interest
	void ComputeQuantities(int current_cycle);


	//  ===================
	//  Auxillary functions
	//  ===================

	// Prints information to terminal
	void PrintInfo();

	// Writes information to file
	void WriteToFile(int current_cycle);

	// Writes information from Parallel computation to file
	void MPIWriteToFile(int number_of_experiments, double T[] ,double E[], double EE[], double EV[], double CV[], 
						double M[], double absM[], double sus[], double acc_states[]);
};