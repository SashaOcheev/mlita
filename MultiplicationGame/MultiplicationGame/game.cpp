
#include "stdafx.h"
#include "game.h"


int CalculateWinner(int limit)
{
	bool doesFirstPlayerWins = false;
	do
	{
		limit = static_cast<int>(ceil(limit / ((doesFirstPlayerWins) ? 2.0 : 5.0)));
		doesFirstPlayerWins = !doesFirstPlayerWins;
	} while (limit > 1);

	return (doesFirstPlayerWins) ? 1 : 2;
}