#include "Ising.h"
#include <mpi.h>


int main(int argc, char *argv[])
{

	// Declearing variables to be read in
	int dimension_of_lattice;
	int mc_cycles;
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

	// Reading in variables
	if ((world_rank == 0) && (argc <= 4))
	{
		std::cout << "Bad Usage: " << argv[0] << std::endl << "Please pass along the following arguments: " << std::endl << 
		"Lattice dimension, Number of Monte-Carlo cycles, a minimum and a maximum temperature and the temperature step, and finaly a filename for the output file." 
		<< std::endl;
		exit(1);
	}

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

	// Calculating the total/per core number of experiments for given initial conditions
	int number_of_experiments = round((T_max-T_min)/(double)T_step);
	int experiments_per_core = number_of_experiments/(double)world_size;

	// Making temperature arrays 
	double temperature[number_of_experiments];
	double local_temperature[experiments_per_core];
	if (world_rank == 0)
	{
		for (int i = 0; i < number_of_experiments; i++)
		{
			temperature[i] = T_min + T_step*i;
		}
	}

	// Starting time of parallel processes
	double TimeStart, TimeStop, TimeTotal;
	TimeStart = MPI_Wtime();

	// Distributing the temperature array to the different cores
	MPI_Scatter(&temperature, experiments_per_core, MPI_DOUBLE, &local_temperature, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// Expectation values to be studied through different cores (local values)
	double local_energy[number_of_experiments];
	double local_energy_squared[number_of_experiments];
	double local_energy_variance[number_of_experiments];
	double local_specific_heat[number_of_experiments];
	double local_magnetization[number_of_experiments];
	double local_absolute_magnetization[number_of_experiments];
	double local_susceptibility[number_of_experiments];

	// Ising Model initialization
	Ising system = Ising(dimension_of_lattice, filename);

	// Parallel Monte Carlo simulation for a given temperature T
	for (int j = 0; j < experiments_per_core; j++)
	{
		double T = local_temperature[j];
		system.InitializeLattice(T, oriented_lattice);
		system.MonteCarloSample(mc_cycles, intermediate_calculations, print_every);

		// Saving the expectation values
		local_energy[j] = system.mean_energy;
		local_energy_squared[j] = system.mean_energy_squared;
		local_energy_variance[j] = system.energy_variance;
		local_specific_heat[j] = system.specific_heat;
		local_magnetization[j] = system.mean_magnetization;
		local_absolute_magnetization[j] = system.mean_absolute_magnetization;
		local_susceptibility[j] = system.susceptibility;
	}

	// Non-local expectation values that will be gathered
	double energy[number_of_experiments];
	double energy_squared[number_of_experiments];
	double energy_variance[number_of_experiments];
	double specific_heat[number_of_experiments];
	double magnetization[number_of_experiments];
	double absolute_magnetization[number_of_experiments];
	double susceptibility[number_of_experiments];
	double temperatures_used[number_of_experiments];

	// Gathering the different values calculated across different cores
	MPI_Gather(&local_energy, experiments_per_core, MPI_DOUBLE, &energy, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Gather(&local_energy_squared, experiments_per_core, MPI_DOUBLE, &energy_squared, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Gather(&local_energy_variance, experiments_per_core, MPI_DOUBLE, &energy_variance, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Gather(&local_specific_heat, experiments_per_core, MPI_DOUBLE, &specific_heat, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Gather(&local_magnetization, experiments_per_core, MPI_DOUBLE, &magnetization, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Gather(&local_absolute_magnetization, experiments_per_core, MPI_DOUBLE, &absolute_magnetization, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Gather(&local_susceptibility, experiments_per_core, MPI_DOUBLE, &susceptibility, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Gather(&local_temperature, experiments_per_core, MPI_DOUBLE, &temperatures_used, experiments_per_core, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// Dumping the data to file from the root core
	if (world_rank == 0)
	{
		TimeStop = MPI_Wtime();
		TimeTotal = TimeStop-TimeStart;

		// Writing out the time spent on the total calculation
		std::cout << "Time spent: " << TimeTotal << " seconds" << "\nProcesses: " << world_size << std::endl;

		system.MPIWriteToFile(number_of_experiments, temperatures_used,  energy, energy_squared, energy_variance
			, specific_heat, magnetization, absolute_magnetization, susceptibility);

	}

	// Terminating MPI
	MPI_Finalize();
	
	return 0;

}