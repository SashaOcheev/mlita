#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>

/* 
-4 - стена
-1 - K - конь
-2 - B -слон
-3 - R -ладья
*/

const int MAX_SIZE = 15;
typedef int Board[MAX_SIZE + 2][MAX_SIZE + 2];
typedef std::pair<size_t, size_t> Coor;

struct Figure
{
	Coor pos;
	int val;
	bool isAlive;

	Figure(Coor coor, int value) :
		pos(coor),
		val(value),
		isAlive(true)
	{

	}
};

struct Figures
{

public:

	int count;

	size_t Size() const
	{
		return m_figures.size();
	}
	
	Figure &operator[](size_t i)
	{
		return m_figures[i];
	}

	Figure operator[](size_t i) const
	{
		return m_figures[i];
	}

private:
	std::vector<Figure> m_figures;

};

void FillLine(Board board, Coor start, Coor const& move)
{
	do
	{
		start.first += move.first;
		start.second += move.second;
		if (board[start.first][start.second] > -4)
			board[start.first][start.second] -= 4;
	} while (board[start.first][start.second] > -4);
}

void BishopMove(Board board, Figure const& figure)
{
	FillLine(board, figure.pos, { -1, -1 });
	FillLine(board, figure.pos, { -1, 1 });
	FillLine(board, figure.pos, { 1, -1 });
	FillLine(board, figure.pos, { 1, 1 });
}

void RookMove(Board board, Figure const& figure)
{
	FillLine(board, figure.pos, { -1, 0 });
	FillLine(board, figure.pos, { 0, -1 });
	FillLine(board, figure.pos, { 0, 1 });
	FillLine(board, figure.pos, { 1, 0 });
}

void KnightOneMove(Board board, Coor const& size, Coor start, Coor const& move)
{
	start.first += move.first;
	start.second += move.second;
	if (start.first > 0 && start.second > 0 && start.first < size.first - 1 && start.second < size.second - 1 && board[start.first][start.second] > -4)
		board[start.first][start.second] -= 4;
}

void KnightMove(Board board, Coor const& size, Figure const& figure)
{
	KnightOneMove(board, size, figure.pos, { -2, -1 });
	KnightOneMove(board, size, figure.pos, { -2, 1 });
	KnightOneMove(board, size, figure.pos, { -1, -2 });
	KnightOneMove(board, size, figure.pos, { -1, 2 });
	KnightOneMove(board, size, figure.pos, { 1, -2 });
	KnightOneMove(board, size, figure.pos, { 1, 2 });
	KnightOneMove(board, size, figure.pos, { 2, -1 });
	KnightOneMove(board, size, figure.pos, { 2, 1 });
}

void MarkCellsUnderAttack(Board board, Coor const& size, Figures const& figures)
{
	for (size_t i = 0; i < figures.Size(); i++)
		if (figures[i].isAlive)
			board[figures[i].pos.first][figures[i].pos.second] = figures[i].val;

	for (size_t i = 0; i < figures.Size(); i++)
	{
		if (figures[i].isAlive)
		{
			switch (figures[i].val)
			{
				case -1:
					KnightMove(board, size, figures[i]);
					break;
				case -2:
					BishopMove(board, figures[i]);
					break;
				case -3:
					RookMove(board, figures[i]);
					break;
				default:
					break;
			}
		}
	}
}

void InitBoard(Board board, Coor const& size, Figures const& figures)
{
	for (size_t i = 0; i < size.first - 1; i++)
		for (size_t j = 0; j < size.second - 1; j++)
			if (i == 0 || j == 0 || i == size.first - 1 || j == size.second - 1)
				board[i][j] = -4;
			else
				board[i][j] = 0;
	
	MarkCellsUnderAttack(board, size, figures);
}

int KingOneMove(std::queue<Coor> & wave, Board board, Coor const& size, Coor start, Coor const& move, Figures & figures)
{
	auto val = board[move.first][move.second];
	start.first += move.first;
	start.second += move.second;
	if (board[start.first][start.second] > -4 && board[start.first][start.second] <= 0)
	{
		board[start.first][start.second] = val + 1;

		if (board[start.first][start.second] == 0)
			wave.push(start);
		else
		{
			for (size_t i = 0; i < figures.Size(); i++)
			{
				if (figures[i].pos == start)
				{
					figures[i].isAlive = false;
					figures.count -= 1;
					auto dist = Func(size, start, figures);//рекурсия
					figures[i].isAlive = true;
					return board[start.first][start.second] + dist;
				}
			}
		}
	}
	return 0;
}

int KingMoves(std::queue<Coor> & wave, Board board, Coor const& size, Figures const& figures)
{
	Coor start = wave.front();
	wave.pop();
	KingMove(board, start, figures);
}

int Func(Coor const& size, Coor const& start, Figures & figures)
{
	Board board;
	InitBoard(board, size, figures);

	std::queue<Coor> wave;
	wave.push(start);

	while (figures.count > 0 && !wave.empty())
	{

	}
}