#include "Ising.h"

int main(int argc, char *argv[])
{

	// Declearing variables to be read in
	int dimension_of_lattice, mc_cycles;
	double temperature;
	std::string filename;

	if (argc <= 4)
	{
		std::cout << "Bad Usage: " << argv[0] << std::endl << "Please pass along the following arguments: " << std::endl << 
		"Lattice dimension, Number of Monte-Carlo cycles, Initial temperature and a filename for the output file."
		<< std::endl;
		exit(1);
	}

	// Reading in variables
	if (argc >= 5)
	{
		dimension_of_lattice = atoi(argv[1]);
		mc_cycles = atoi(argv[2]);
		temperature =  atof(argv[3]);
		filename = argv[4];

	}

	int world_size, rank;

	// MPI_Init(&nargc, &argv);
	// MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	// MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


	// Ising Model
	Ising system = Ising(dimension_of_lattice, filename);

	// On and off functions
	bool intermediate_calculations = false;
	bool oriented_lattice = false;

	for (int i = 0; i < 100; i++)
	{
		system.InitializeLattice(temperature, oriented_lattice, i);
		system.MonteCarloSample(mc_cycles, intermediate_calculations);
	}
	return 0;

}