#include "functions.h"

int main(int argc, char *argv[])
{
	int N = 1000;
	int transactions = 1e7;
	int simulations = 1e2;
	double m_0 = 1;
	double lambda = 0;
	double alpha = 2;

	std::string savefile;
	savefile = argv[1];

	// Initializing the model
	StockMarketModel StockMarket = StockMarketModel(N, transactions, simulations, m_0, lambda, alpha, savefile);
	StockMarket.Simulate();

	return 0;
}
