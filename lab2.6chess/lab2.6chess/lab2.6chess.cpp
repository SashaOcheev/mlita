// lab2.6chess.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iomanip>

const int SIZE = 15;
typedef int Mat[SIZE + 2][SIZE + 2];

struct Coor
{
	int i;
	int j;

	Coor()
	{
		i = 0;
		j = 0;
	}
};

struct Figure
{
	int i;
	int j;
	int val;

	Figure(int x, int y, int value)
	{
		i = x;
		j = y;
		val = value;
	}
};

typedef std::list<Figure> Figures;

bool move(Mat board, const Coor size, const Figure figure, const int i, const int j)
{
	if (figure.i + i >= 0 && figure.i + i < size.i && figure.j + j >= 0 && figure.j + j < size.j && board[figure.i + i][figure.j + j] >= -4)
	{
		if (board[figure.i + i][figure.j + j] > -4)
		{
			board[figure.i + i][figure.j + j] -= 4;
			if (board[figure.i + i][figure.j + j] < -4)
				return false;
		}
		return true;
	}
	return false;
}

void oneRecStep(Mat board, const Coor size, Figure figure, const int i, const int j)
{
	if (move(board, size, figure, i, j))
	{
		figure.i += i;
		figure.j += j;
		oneRecStep(board, size, figure, i, j);
	}
}

void bishop(Mat board, const Coor size, Figure figure)
{
	oneRecStep(board, size, figure, -1, -1);
	oneRecStep(board, size, figure, -1, 1);
	oneRecStep(board, size, figure, 1, 1);
	oneRecStep(board, size, figure, 1, -1);
}

void rook(Mat board, const Coor size, Figure figure)
{
	oneRecStep(board, size, figure, -1, 0);
	oneRecStep(board, size, figure, 0, -1);
	oneRecStep(board, size, figure, 0, 1);
	oneRecStep(board, size, figure, 1, 0);
}

void knight(Mat board, const Coor size, Figure figure)
{
	move(board, size, figure, -2, -1);
	move(board, size, figure, -2, 1);
	move(board, size, figure, -1, 2);
	move(board, size, figure, 1, 2);
	move(board, size, figure, 2, 1);
	move(board, size, figure, 2, -1);
	move(board, size, figure, 1, -2);
	move(board, size, figure, -1, -2);
}

void filling(Mat board, const Coor size, Figures figures)
{
	for (Figures::iterator it = figures.begin(); it != figures.end(); it++)
		board[it->i][it->j] = it->val;
	for (Figures::iterator it = figures.begin(); it != figures.end(); it++)
	{
		if (it->val == -1)
			knight(board, size, *it);
		else if (it->val == -2)
			bishop(board, size, *it);
		else
			rook(board, size, *it);
	}
}

int func(Coor size, Figures figures, Coor start)
{
	size.i += 2;
	size.j += 2;
	Mat board;
	for (int i = 0; i < size.i; i++)
		for (int j = 0; j < size.j; j++)
			if (i == 0 || j == 0 || i == size.i - 1 || j == size.j - 1)
				board[i][j] = -4;
			else
				board[i][j] = 0;
	filling(board, size, figures);

	return 0;
}

int main()
{
	std::ifstream fin("input.txt", std::ios_base::in);

	Coor size;
	fin >> size.i >> size.j;
	fin.get();

	char ch;
	Figures figures;
	
	Coor start;
	for (int i = 0; i < size.i; i++)
	{
		for (int j = 0; j < size.j; j++)
		{
			int val = 0;
			ch = fin.get();
			if (ch == '*')
			{
				start.i = i + 1;
				start.j = j + 1;
			}
			else if (ch == 'K')
				val = -1;//конь
			else if (ch == 'B')
				val = -2;//слон
			else if (ch == 'R')
				val = -3;//ладья
			if (val)
				figures.push_back(Figure(i + 1, j + 1, val));
		}
		fin.get();
	}

	func(size, figures, start);

	std::ofstream fout("output.txt", std::ios_base::out | std::ios_base::trunc);
	return 0;
}
