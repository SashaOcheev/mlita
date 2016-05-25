
#include "stdafx.h"
#include "game.h"


int CalculateWinner(int limit)
{
	int winner = 1;
	while (limit > 1)
	{
		limit = static_cast<int>(ceil(limit / ((winner) ? 5.0 : 2.0)));
		winner = abs(winner - 1);
	}

	return winner + 1;
}