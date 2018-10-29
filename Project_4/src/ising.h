#include <armadillo>
#include <string>


class Ising
{
	//  
	//  Ising model
	// 

private:

//  =================
//  System properties
//  =================

	int dimension_of_lattice;
	int number_of_spins;
	int number_of_mc_cycles;
	int number_of_accepted_states;
	double temperature;

	arma::mat lattice;
	arma::vec expectation_values;
	arma::vec energy_difference;

//  ======================
//  Quantities of interest
//  ======================

	// Energy
	double energy;
	double mean_energy;
	double energy_variance;
	double specific_heat;

	// Magnetization
	double magnetization;
	double mean_magnetization;
	double susceptibility;
	double mean_absoloute_magnetization;

//  =======
//  Methods
//  =======

	// Periodic boundary conditions index
	int PBC(int index, int limit, int offset);

	// The metropolis algorithm
	void Metropolis();

	// Extracting energy
	double getEnergy(int x, int y);

public:

	//  =======
	//  Methods
	//  =======

	// Constructor
	Ising(int dimension_of_lattice);

	// Initiallizing the system
	void InitializeLattice(double temperature);

	// Monte Carlo integration
	void MonteCarloSample(int N);


};