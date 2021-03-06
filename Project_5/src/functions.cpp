#include "functions.h"

StockMarketModel::StockMarketModel(int N, int transactions, int simulations, double m_0, double lambda, double alpha, double gamma, std::string savefile)
{
	// The constructor which initializes the stock market model
	this->N = N;
	this->transactions = transactions;
	this->simulations = simulations;
	this->m_0 = m_0;
	this-> savefile = savefile;

	// Parameters
	this->lambda = lambda;					// Saving criterion fraction
	this->alpha = alpha;					// Power law parameter for nearest neighbor interactions
	this->gamma = gamma; 					// Power law parameter for former transactions

	// Vector containing the wealth of all agents
	this->agents = arma::vec(N).fill(m_0);

	// Vector containing the total averaged wealth of all agents
	this->total_average_agents = arma::vec(N);

	// Matrix containing number of interactions between all agents
	this->C = arma::mat(N,N).fill(0);
};


void StockMarketModel::Trade()
{
	// Function that performs a trade between an agent and another

	// Initialzing seed and the Mersienne random generator
	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::uniform_int_distribution<int> RNG_int(0, N-1);					// Uniform integer distribution in (0, N)
	std::uniform_real_distribution<double> RNG_real(0.0, 1.0);			// Uniform double distribution in (0.1, 1.0)

	// Reseting agent and transaction matrices
	C.fill(0);
	agents.fill(m_0);

	// Parameters which will be used to determine equilibrium
	int transaction_interval = 1e4;
	double variance, averaged_variance;

	// Initial large value so that the first average variance is always saved
	double previous_averaged_variance = 1e10;

	// Performing given number of transactions
	for (int i = 0; i < transactions; i++)
	{
		// Picking two random agents
		int agent_i = RNG_int(generator);
		int agent_j = RNG_int(generator);

		// Extracting wealth of respective agents
		double m_i = agents(agent_i);
		double m_j = agents(agent_j);

		// Extracting the current number of transactions between the two agents
		int C_ij = C(agent_i, agent_j);

		// Defining likelihood of a transaction between the two arbritarily chosen agents

		// Checking if:
		// 	- agent i and j are the same agent
		// 	- likelihood is smaller than some random number
		// If both conditions are false the loop breaks and the agents are allowed to perform a transaction
		while ((agent_i == agent_j) || (((pow(fabs(m_i - m_j), -alpha)) * (pow(C_ij + 1, gamma))) < RNG_real(generator)))
		{
			// Picking two new agents
			agent_i = RNG_int(generator);
			agent_j = RNG_int(generator);

			// Extracting their wealth
			m_i = agents(agent_i);
			m_j = agents(agent_j);

			// Update the current number of transactions
			C_ij = C(agent_i, agent_j);

		}
		// Finding a random monetary value exchanged during transaction
		double epsilon = RNG_real(generator);

		// Computing the traded money delta_m
		double delta_m = (1-lambda)*(epsilon*m_j - (1 - epsilon)*m_i);

		// Updating the new wealth of both agents
		agents(agent_i) += delta_m;
		agents(agent_j) -= delta_m;

		// Update the number of transactions
		C(agent_i, agent_j) += 1;
		C(agent_j, agent_i) += 1;

		// Checking if the system has reached an equilibrium
		// Updating variance for each transaction in a interval
		variance += arma::var(agents);

		// Enters loop at the end of a transaction interval
		if (i % transaction_interval == 0)
		{
			// Averaging the variance over the interval
			averaged_variance = variance/transaction_interval;

			// Checking if variance changed by less than 0.5%
			if ((fabs(previous_averaged_variance - averaged_variance) / (previous_averaged_variance)) < 0.005)
			{
				// Equilibrium has been reached.
				break;
			}

			else
			{
				// The averaged variance is stored for later use
				previous_averaged_variance = averaged_variance;
			}

			// Reseting the variance
			variance = 0;
		}
	}
}


void StockMarketModel::Simulate()
{
	// Function that simulates the system a given number of times and computes
	// the average wealth distribution

	// Timing the simulation
	clock_t start, stop;

	// Starting the clock
	start = clock();

	// Performing a given number of simulations
	for (int i = 0; i < simulations; i++)
	{
		// Activating the Trade function
		Trade();

		// Sorting the agents array and adding it to the total
		total_average_agents += arma::sort(agents);
	}

	// Averaging over all simulations and saving to file
	total_average_agents /= simulations;
	DumpToFile();

	// Stopping the clock
	stop = clock();

	// Printing the time spent
	std::cout << "Time spent: " << double (stop - start)/CLOCKS_PER_SEC << " seconds." << std::endl;
}


void StockMarketModel::DumpToFile()
{
	// Writing the final wealth distribution of all N agents to file
	using namespace std;

	ofstream ofile;
	ofile.open("data/" + savefile + ".dat");
	ofile << setiosflags(ios::showpoint | ios::uppercase);

	for (int i = 0; i < N; i++)
	{
		ofile << setprecision(8) << total_average_agents(i) << "\n";
	}

	ofile.close();
}
