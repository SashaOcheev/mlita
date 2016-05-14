// TimberCut2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TimberCount2.h"


unsigned MinCost(unsigned length, unsigned timberCount)
{
	std::multiset<unsigned> sums;

	unsigned res = 0;

	for (size_t i = 0; i < timberCount; i++)
		sums.emplace(1);
	sums.emplace(length - timberCount);

	while (sums.size() > 1)
	{
		auto it = sums.begin();
		res += *sums.emplace(*it + *(++it));
		sums.erase(it);
		sums.erase(sums.begin());
	}

	return res;

}