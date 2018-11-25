#include "functions.h"

StockMarketModel::StockMarketModel(int N, int transactions, int simulations, double m_0)
{
	// The constructor
	// Initializing the stock market model
	this->N = N;
	this->transactions = transactions;
	this->simulations = simulations;
	this->m_0 = m_0;

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
	std::uniform_int_distribution<int> RNG(0, N);

	// Extracting two random agents
	int agent_i = RNG(generator);
	int agent_j = RNG(generator);

	// Extracting wealth of respective agents
	double m_i = agents(agent_i);
	double m_j = agents(agent_j);



}