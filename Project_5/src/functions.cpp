#include "functions.h"

StockMarketModel::StockMarketModel(int N, int transactions, int simulations, double m_0, std::string savefile)
{
	// The constructor
	// Initializing the stock market model
	this->N = N;
	this->transactions = transactions;
	this->simulations = simulations;
	this->m_0 = m_0;
	this-> savefile = savefile;

	// Vector containing the wealth of all agents
	arma::vec agents(N);
	agents.fill(m_0);
	this->agents = agents;
};


void StockMarketModel::Transaction()
{
	// Initialzing seed and the Mersienne random generator
	std::random_device rd;
	std::mt19937_64 generator(rd());
	std::uniform_int_distribution<int> RNG_int(0, N-1);
	std::uniform_real_distribution<double> RNG_real(0.1, 1.0);

	for (int i = 0; i < transactions; i++)
	{
		// Extracting two random agents
		int agent_i = RNG_int(generator);
		int agent_j = RNG_int(generator);	

		// Extracting wealth of respective agents
		double m_i = agents(agent_i);
		double m_j = agents(agent_j);	

		// Finding the random monetary value exchanged during transaction
		double epsilon = RNG_real(generator);	

		// Computing delta m
		double delta_m = (epsilon*m_j - (1 - epsilon)*m_i);	

		// Updating the money of the agents
		agents(agent_i) += delta_m;
		agents(agent_j) -= delta_m;
	}
}


void StockMarketModel::DumpToFile()
{
	using namespace std;

	ofstream ofile;
	ofile.open("data/" + savefile + ".dat", ios::app);
	ofile << setiosflags(ios::showpoint | ios::uppercase);
	for (int i = 0; i < N; i++)
	{
		ofile << setprecision(8) << agents(i) << "\n";
	}
	ofile.close();
}
