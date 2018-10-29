#include "Ising.h"

int main(int argc, char *argv[])
{

	int dimension_of_lattice = atoi(argv[1]);
	int N = atoi(argv[2]);
	double temperature = 1;


	Ising system = Ising(dimension_of_lattice);
	system.InitializeLattice(temperature);
	system.MonteCarloSample(N);

	return 0;

}