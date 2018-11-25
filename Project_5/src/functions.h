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
	int transactions;		// Number of transactions
	int simulations;		// Number of simulations
	std::string savefile;	// Name of outputfile

	// Initial wealth of all agents
	double m_0;

	// Vector containing the wealth of all agents
	arma::vec agents;



	// Constructor which initializes the model
	StockMarketModel(int N, int transactions, int simulations, double m_0, std::string savefile);

	// Functions
	void Transaction();
	void DumpToFile();

};