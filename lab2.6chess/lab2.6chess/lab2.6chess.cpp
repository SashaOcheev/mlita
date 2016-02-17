// lab2.6chess.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iomanip>

struct Figure
{
	int i;
	int j;
	int val;
	Figure(int x, int y, int value);
};

const int SIZE = 15;
typedef int Mat[SIZE + 2][SIZE + 2];
typedef std::list<Figure> Figures;

struct Coor
{
	int i;
	int j;
	Coor(int I = 0, int J = 0);
};

bool Move(Mat board, const Coor size, const Figure figure, const int i, const int j);
void OneFigureStep(Mat board, const Coor size, Figure figure, const int i, const int j);
void Bishop(Mat board, const Coor size, Figure figure);
void Rook(Mat board, const Coor size, Figure figure);
void Knight(Mat board, const Coor size, Figure figure);
void Filling(Mat board, const Coor size, Figures figures);
void kingStep(std::queue<Coor> &kill, std::queue<Coor> &wave, Mat board, Coor start, Coor shift);
int Func(Coor size, Figures figures, Coor start);

Coor::Coor(int I, int J)
{
	i = I;
	j = J;
}

Figure::Figure(int x, int y, int value)
{
	i = x;
	j = y;
	val = value;
}

bool Move(Mat board, const Coor size, const Figure figure, const int i, const int j)
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

void OneFigureStep(Mat board, const Coor size, Figure figure, const int i, const int j)
{
	if (Move(board, size, figure, i, j))
	{
		figure.i += i;
		figure.j += j;
		OneFigureStep(board, size, figure, i, j);
	}
}

void Bishop(Mat board, const Coor size, Figure figure)
{
	OneFigureStep(board, size, figure, -1, -1);
	OneFigureStep(board, size, figure, -1, 1);
	OneFigureStep(board, size, figure, 1, 1);
	OneFigureStep(board, size, figure, 1, -1);
}

void Rook(Mat board, const Coor size, Figure figure)
{
	OneFigureStep(board, size, figure, -1, 0);
	OneFigureStep(board, size, figure, 0, -1);
	OneFigureStep(board, size, figure, 0, 1);
	OneFigureStep(board, size, figure, 1, 0);
}

void Knight(Mat board, const Coor size, Figure figure)
{
	Move(board, size, figure, -2, -1);
	Move(board, size, figure, -2, 1);
	Move(board, size, figure, -1, 2);
	Move(board, size, figure, 1, 2);
	Move(board, size, figure, 2, 1);
	Move(board, size, figure, 2, -1);
	Move(board, size, figure, 1, -2);
	Move(board, size, figure, -1, -2);
}

void Filling(Mat board, const Coor size, Figures figures)
{
	for (Figures::iterator it = figures.begin(); it != figures.end(); it++)
		board[it->i][it->j] = it->val;
	for (Figures::iterator it = figures.begin(); it != figures.end(); it++)
	{
		if (it->val == -1)
			Knight(board, size, *it);
		else if (it->val == -2)
			Bishop(board, size, *it);
		else
			Rook(board, size, *it);
	}
}

void kingStep(std::queue<Coor> &kill, std::queue<Coor> &wave, Mat board, Coor start, Coor shift)
{
	Coor newPos(start.i + shift.i, start.j + shift.j);
	if (board[newPos.i][newPos.j] > -4 && board[newPos.i][newPos.j] <= 0)
	{
		if (board[newPos.i][newPos.j] == 0)
			wave.push(newPos);
		else
			kill.push(newPos);
		board[newPos.i][newPos.j] = board[start.i][start.j] + 1;
	}
}

int Func(Coor size, Figures figures, Coor start)
{
	if (!figures.size())
		return 0;

	Mat board;
	for (int i = 0; i < size.i; i++)
		for (int j = 0; j < size.j; j++)
			if (i == 0 || j == 0 || i == size.i - 1 || j == size.j - 1)
				board[i][j] = -4;
			else
				board[i][j] = 0;
	Filling(board, size, figures);

	std::queue<Coor> kill;
	std::queue<Coor> wave;
	wave.push(start);
	while (!wave.empty() && figures.size())
	{
		start = wave.front();
		wave.pop();
		kingStep(kill, wave, board, start, Coor(-1, -1));
		kingStep(kill, wave, board, start, Coor(-1, 0));
		kingStep(kill, wave, board, start, Coor(-1, 1));
		kingStep(kill, wave, board, start, Coor(0, 1));
		kingStep(kill, wave, board, start, Coor(1, 1));
		kingStep(kill, wave, board, start, Coor(1, 0));
		kingStep(kill, wave, board, start, Coor(1, -1));
		kingStep(kill, wave, board, start, Coor(0, -1));
	}

	if (!kill.size())
		return -1;

	int min = -1;
	while (kill.size())
	{
		Coor tempKill = kill.front();
		kill.pop();
		Figures tempFigures = figures;
		for (Figures::iterator it = tempFigures.begin(); it != tempFigures.end();)
		{
			if (it->i == tempKill.i && it->j == tempKill.j)
			{
				tempFigures.erase(it++);
				break;
			}
			else
				it++;
		}
		int temp = Func(size, tempFigures, tempKill);
		if (temp >= 0)
		{
			if (min == -1)
				min = temp + board[tempKill.i][tempKill.j];
			else if (temp + board[tempKill.i][tempKill.j] < min + board[tempKill.i][tempKill.j])
				min = temp + board[tempKill.i][tempKill.j];
		}
	}
	return min;
}

int main()
{
	std::ifstream fin("input1.txt", std::ios_base::in);

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
	size.i += 2;
	size.j += 2;

	int temp = Func(size, figures, start);
	std::ofstream fout("output.txt", std::ios_base::out | std::ios_base::trunc);
	fout << temp;
	return 0;
}