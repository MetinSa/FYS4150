#include <iostream>
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
	int transactions;		// Number of transactions
	int simulations;		// Number of simulations

	double m_0;				// Initial wealth of all agents
	arma::vec agents;		// Vector containing the wealth of all agents

	std::string savefile;	// Name of outputfile

	// Constructor which initializes the model
	StockMarketModel(int N, int transactions, int simulations, double m_0);

	// Functions
	void Transaction();


};