#include "functions.h"

int main(int argc, char *argv[])
{
	int N = 500;
	int transactions = 1e7; 
	int simulations = 1e3; 
	double m_0 = 100;

	std::string savefile;
	if (argc > 1)
	{
		savefile = argv[1];
	}
	else
	{
		std::cout << "Please provide filename in command line." << std::endl;
		return 1;
	}

	// Initializing the model
	StockMarketModel StockMarket(N, transactions, simulations, m_0, savefile);
	StockMarket.Simulate();

	return 0;
}
