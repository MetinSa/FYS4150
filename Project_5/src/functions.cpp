#include "functions.h"
#include <omp.h>

StockMarketModel::StockMarketModel(int N, int transactions, int simulations, double m_0, double lambda, double alpha, double gamma, std::string savefile)
{
	// The constructor
	// Initializing the stock market model
	this->N = N;
	this->transactions = transactions;
	this->simulations = simulations;
	this->m_0 = m_0;
	this-> savefile = savefile;

	// Parameters
	this->lambda = lambda;								// Saving criterion fraction
	this->alpha = alpha;									// Power law parameter for nearest neighbor interactions
	this->gamma = gamma; 									// Power law parameter for former transactions

	// Vector containing the wealth of all agents
	arma::vec agents(N);
	agents.fill(m_0);
	this->agents = agents;

	// Vector containing the total averaged wealth of all agents
	arma::vec total_average_agents(N);
	this->total_average_agents = total_average_agents;

	// Matrix containing number of interactions between all agents
	arma::mat C(N,N);
	C.fill(0);
	this->C = C;

};



void StockMarketModel::Trade(arma::vec &agents, arma::mat &C)
	{
	//std::cout << C << std::endl;

	// Function that performs a trade between an agent and another

	// Initialzing seed and the Mersienne random generator
	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::uniform_int_distribution<int> RNG_int(0, N-1);					// Uniform integer distribution in (0, N)
	std::uniform_real_distribution<double> RNG_real(0.0, 1.0);			// Uniform double distribution in (0.1, 1.0)

	// Parameters which will be used to determine equilibrium
	int transaction_interval = 1e4;
	double variance, averaged_variance;

	// Initial large value so that the first average variance is always saved
	double previous_averaged_variance = 1e10;

	int idum = 0;
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
		int current_transactions = C(agent_i, agent_j);

		// Defining likelihood of a transaction between the two arbritarily chosen agents

		// Checking if:
		// - agent i and j are the same agent
		// - likelihood is smaller than some random number (throwing dice)
		// If conditions are met the loop breaks and the agents are allowed to trade
		while ( (agent_i == agent_j) || ( ((pow(fabs(m_i - m_j), -alpha)) * (pow(current_transactions + 1, gamma))) < RNG_real(generator)) )
		{
			// Picking two new agents
			agent_i = RNG_int(generator);
			agent_j = RNG_int(generator);

			// Extracting their wealth
			m_i = agents(agent_i);
			m_j = agents(agent_j);

			// Update the current number of transactions between the two new agents
			current_transactions = C(agent_i, agent_j);

			// Checking how many times two agents arent allowed to trade
			idum ++;

		}
		// std::cout << "out" << std::endl;
		// Finding a random monetary value exchanged during transaction epsilon
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

		// Enters loop at the end of an interval
		if (i % transaction_interval == 0)
		{
			// Averaging the variance over the interval
			averaged_variance = variance/transaction_interval;

			// Checking if the average variance has changed by less than 0.5% during the last transaction interval
			if ((fabs(previous_averaged_variance - averaged_variance) / fabs(previous_averaged_variance)) < 0.005)
			{

				// Equilibrium has been reached. Ending the Trade algorithm
				break;
			}
			// If variance statement is not passed, the averaged variance is saved for later comparison
			else
			{
				previous_averaged_variance = averaged_variance;
			}

			// reseting the variance
			variance = 0;
		}
	}
	// Printing the number of times agents werent allowed to trade becaused of likelihood per simulation
	//std::cout << idum << std::endl;
	//std::cout << C << std::endl;

}


void StockMarketModel::Simulate()
{
	// Function that simulates the system a given number of times and computes
	// the average wealth distribution

	// Timing the simulation
	clock_t start, stop;
	int thread_num, n_threads;

	arma::vec agentscopy = agents;
	arma::mat C_copy = C;
	arma::mat total_average_agents_per_thread;
	// Starting the clock
	start = clock();


	// Performing a given number of simulations
#pragma omp parallel private(agents, thread_num, C) shared(n_threads, total_average_agents_per_thread)
	{
#pragma omp master
		{
			n_threads = omp_get_num_threads();
			total_average_agents_per_thread = arma::mat(N, n_threads);
		}
		agents = agentscopy;
		C = C_copy;
		thread_num = omp_get_thread_num();

#pragma omp for
		for (int i = 0; i < simulations; i++)
			{
				// Activating the Trade function
				Trade(agents, C);
				// Sorting the agents array and adding it to the total
				total_average_agents_per_thread.col(thread_num) += arma::sort(agents);
			}
#pragma omp master
		{
			total_average_agents = sum(total_average_agents_per_thread, 1);
		}
	}

	// Saving the final results by dumping them to a file
	total_average_agents /= simulations;
	DumpToFile();

	// Stopping the clock
	stop = clock();
	// Printing the time spent
	std::cout << "Time spent: " << double (stop - start)/(n_threads*CLOCKS_PER_SEC) << " seconds." << std::endl;
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
