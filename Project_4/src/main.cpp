#include "Ising.h"

int main(int argc, char *argv[])
{

	int dimension_of_lattice = atoi(argv[1]);
	int mc_cycles = atoi(argv[2]);
	double temperature =  atof(argv[3]);
	std::string filename = argv[4];
	bool intermediate_calculations = true;
	bool oriented_lattice = false;

	Ising system = Ising(dimension_of_lattice, filename);
	system.InitializeLattice(temperature, oriented_lattice);
	system.MonteCarloSample(mc_cycles, intermediate_calculations);

	return 0;

}