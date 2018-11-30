#include "functions.h"

int main(int argc, char *argv[])
{
	int N = 1000;
	int transactions = 1e7;
	int simulations = 1e4;
	double m_0 = 100;
	double lambda;
	double alpha;
	double gamma;
	std::string savefile;

	if (argc > 4)
	{
		savefile = argv[1];
		lambda = atof(argv[2]);
		alpha = atof(argv[3]);
		gamma = atof(argv[4]);
	}
	else
	{
		std::cout << "Please provide filename, lambda, alpha and gamma (in order) in command line." << std::endl;
		return 1;
	}

	// Initializing the model
	StockMarketModel StockMarket = StockMarketModel(N, transactions, simulations, m_0, lambda, alpha, gamma, savefile);
	StockMarket.Simulate();

	return 0;
}
