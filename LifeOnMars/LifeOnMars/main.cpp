#include "stdafx.h"
#include "LifeOnMars.h"


int main(int argc, char* argv[])
{
	auto startTime = std::clock();

	std::ifstream inputFile(argv[1]);

	CGraph graph;
	graph.InitFromText(inputFile);
	auto res = graph.RunAlgorithm();

	std::ofstream outputFile(argv[2]);
	outputFile << std::fixed << std::setprecision(2) << res;
	
	std::cout << std::clock() - startTime;
	return 0;
}