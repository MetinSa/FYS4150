#include "functions.h"

int main(int argc, char *argv[])
{
	int N = 1000;
	int transactions = 1e7;
	int simulations = 1e4;
	double m_0 = 100;
	double lambda = 0;
	double alpha = 0;
	double gamma = 0;
	std::string savefile;

	if (argc > 1)
	{
		savefile = argv[1];
		if (argc > 2) {lambda = atof(argv[2]);}
		if (argc > 3) {alpha = atof(argv[3]);}
		if (argc > 4) {gamma = atof(argv[4]);}
		if (argc > 5) {simulations = atof(argv[5]);}
		if (argc > 6) {N = atof(argv[6]);}
		if (argc > 7) {transactions = atof(argv[7]);}
		if (argc > 8) {m_0 = atof(argv[8]);}
	}
	else
	{
		std::cout << "Please provide the following parameters in the command line." << std::endl
				<< "    1. Filename (Without file extension, will be saved as .dat)" << std::endl
				<< "    2. lambda, fraction of savings (or tax) (optional, standard 0)" << std::endl
				<< "    3. alpha (optional standard 0)" << std::endl
				<< "    4. gamma (optional, standard 0)" << std::endl
				<< "    5. Number of simulations (optional, standard 1e4)" << std::endl
				<< "    6. Number of agents (optional, standard 1000)" << std::endl
				<< "    7. Number of transactions (optional, standard 1e7)" << std::endl
				<< "    8. M_0, average fortune (optional, standard 100)" << std::endl;
		return 1;
	}

	// Initializing the model
	StockMarketModel StockMarket = StockMarketModel(N, transactions, simulations, m_0, lambda, alpha, gamma, savefile);
	StockMarket.Simulate();

	return 0;
}
