#include "functions.h"

int main()
{
	int N = 1e2;
	int transactions = 1e2; 
	int simulations = 1e2; 
	double m_0 = 10;

	// Initializing the model
	StockMarketModel StockMarket = StockMarketModel(N, transactions, simulations, m_0);
	StockMarket.Transaction();

	return 0;
}