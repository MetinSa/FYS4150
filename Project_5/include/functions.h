#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <ctime>
#include <armadillo>

class StockMarketModel
{
	// Class which simulates financial transactions among financial
	// agents using the Monte Carlo methhod.

public:

	// Model spesifics
	int N;					// Number of agents
	int transactions;		// Number of trades
	int simulations;		// Number of simulations
	std::string savefile;	// Name of outputfile

	// Initial wealth of all agents
	double m_0;

	// Parameters used to estimate equilibrium
	double transacton_interval;
	double variance;

	// Vector containing the wealth of all agents
	arma::vec agents;

	// Vector containing the total averaged wealth of all agents
	arma::vec total_average_agents;

	// Constructor which initializes the model
	StockMarketModel(int N, int transactions, int simulations, double m_0, std::string savefile);

	// Functions
	void Trade(arma::vec &agents);			// Performing the transactions
	void Simulate();		// Simulating the system
	void DumpToFile();		// Dumping results to file

};
