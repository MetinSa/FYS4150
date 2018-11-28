#include "functions.h"

int main(int argc, char *argv[])
{
	int N = 500;
	int transactions = 1e7;
	int simulations = 1e3;
	double m_0 = 100;
	double lambda = 0.0;

	std::string savefile;
	savefile = argv[1];

	// Initializing the model
	StockMarketModel StockMarket = StockMarketModel(N, transactions, simulations, m_0, lambda, savefile);
	StockMarket.Simulate();

	return 0;
}
