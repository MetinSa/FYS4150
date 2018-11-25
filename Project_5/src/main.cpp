#include "functions.h"

int main()
{
	int N = 500;
	int transactions = 1e7; 
	int simulations = 1e2; 
	double m_0 = 100;
	std::string savefile = "test";

	// Initializing the model
	StockMarketModel StockMarket = StockMarketModel(N, transactions, simulations, m_0, savefile);
	// StockMarket.agents.print();
	StockMarket.Transaction();
	StockMarket.DumpToFile();

	return 0;
}