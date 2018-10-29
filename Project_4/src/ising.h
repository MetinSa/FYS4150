#include <armadillo>
#include <string>


class ising
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

	arma::mat spin_matrix;
	arma::vec expectation_values;
	arma::ved delta_energies;

//  ======================
//  Quantities of interest
//  ======================

	// Energy
	double energy;
	double mean_energy;
	double energy_variance;
	double specific_heat

	// Magnetization
	double magnetization
	double mean_magnetization;
	double susceptibility;
	double mean_absoloute_magnetization;

//  =======
//  Methods
//  =======

	// Periodic boundary conditions index
	int PBC();

	// The metropolis algorithm
	void metropolis();


}