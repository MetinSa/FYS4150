#include "Ising.h"
#include <mpi.h>


int main(int argc, char *argv[])
{

	// Declearing variables to be read in
	int dimension_of_lattice, mc_cycles;
	double T_min, T_max, T_step;
	std::string filename;

	// Initializing the MPI environment
	MPI_Init(&argc, &argv);

	// Getting the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Getting the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if ((world_rank == 0) && (argc <= 4))
	{
		std::cout << "Bad Usage: " << argv[0] << std::endl << "Please pass along the following arguments: " << std::endl << 
		"Lattice dimension, Number of Monte-Carlo cycles, Initial temperature and a filename for the output file."
		<< std::endl;
		exit(1);
	}

	// Reading in variables
	if ( (world_rank == 0) && (argc >= 7))
	{
		dimension_of_lattice = atoi(argv[1]);
		mc_cycles = pow(10, atoi(argv[2]));
		T_min =  atof(argv[3]);
		T_max =  atof(argv[4]);
		T_step =  atof(argv[5]);
		filename = argv[6];
	}

	// On and off functions
	bool intermediate_calculations = false;
	bool oriented_lattice = false;
	int print_every = 1;

	// Broadcasting initial conditions to all processes
	MPI_Bcast(&dimension_of_lattice, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&mc_cycles, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&T_min, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&T_max, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&T_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// Starting time of parallel processes
	double TimeStart, TimeStop, TimeTotal;
	TimeStart = MPI_Wtime();

	// Ising Model initialization
	Ising system = Ising(dimension_of_lattice, filename);

	// Parallel Monte Carlo simulation for a temperature range
	for (double temperature = T_min; temperature <= T_max; temperature += T_step)
	{
		system.InitializeLattice(temperature, oriented_lattice);
		system.MonteCarloSample(mc_cycles, intermediate_calculations, print_every);
		system.reduced_expectation_values = arma::vec(5);

		for (int i = 0; i < 5; i++)
		{
			MPI_Reduce(&system.expectation_values_list(i), &system.reduced_expectation_values(i), 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		}

		if (world_rank == 0)
		{
			// Normalize the reduced expectation values 
			system.reduced_expectation_values /= world_size;
			system.WriteToFileMPI(system.reduced_expectation_values);
		}
	}

	if (world_rank == 0)
	{
		TimeStop = MPI_Wtime();
		TimeTotal = TimeStop-TimeStart;
		std::cout << "Time spent: " << TimeTotal << " seconds" << "\nProcesses: " << world_size << std::endl;

	}


	MPI_Finalize();




	// system.InitializeLattice(temperature, oriented_lattice);
	// system.MonteCarloSample(mc_cycles, intermediate_calculations, print_every);
	// system.PrintInfo();
	
	return 0;

}