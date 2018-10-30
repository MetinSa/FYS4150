#include "Ising.h"

int main(int argc, char *argv[])
{

	int dimension_of_lattice = atoi(argv[1]);
	int N = atoi(argv[2]);
	std::string filename = argv[3];
	double temperature = 2.4;
	bool intermediate_calculations = true;
	bool oriented_lattice = true;

	Ising system = Ising(dimension_of_lattice, filename);
	system.InitializeLattice(temperature, oriented_lattice);
	system.MonteCarloSample(N, intermediate_calculations);

	return 0;

}