// lab2.6chess.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iomanip>

struct Figure
{
	int ln;
	int col;
	bool isAlive;
	int val;
	Figure(int Ln, int Col, int value);
};

const int SIZE = 15;
typedef int Mat[SIZE + 2][SIZE + 2];
typedef std::list<Figure> Figures;

struct Coor
{
	int ln;
	int col;
	Coor(int Ln = 0, int Col = 0);
};

bool Move(Mat board, const Coor &size, const Figure &figure, const int ln, const int col);
void OneFigureStep(Mat board, const Coor &size, Figure &figure, const int ln, const int col);
void Bishop(Mat board, const Coor &size, Figure &figure);
void Rook(Mat board, const Coor &size, Figure &figure);
void Knight(Mat board, const Coor &size, Figure &figure);
void Filling(Mat board, const Coor &size, Figures &figures);
void kingStep(std::queue<Coor> &kill, std::queue<Coor> &wave, Mat board, Coor &start, Coor &shift);
int Func(Coor &size, Figures figures, Coor start);

Coor::Coor(int Ln, int Col)
{
	ln = Ln;
	col = Col;
}

Figure::Figure(int x, int y, int value)
{
	ln = x;
	col = y;
	isAlive = true;
	val = value;
}

bool Move(Mat board, const Coor &size, const Figure &figure, const int ln, const int col)
{
	if (figure.ln + ln >= 0 && figure.ln + ln < size.ln && figure.col + col >= 0 && figure.col + col < size.col && board[figure.ln + ln][figure.col + col] >= -4)
	{
		if (board[figure.ln + ln][figure.col + col] > -4)
		{
			board[figure.ln + ln][figure.col + col] -= 4;
			if (board[figure.ln + ln][figure.col + col] < -4)
				return false;
		}
		return true;
	}
	return false;
}

void OneFigureStep(Mat board, const Coor &size, Figure &figure, const int ln, const int col)
{
	if (Move(board, size, figure, ln, col))
	{
		figure.ln += ln;
		figure.col += col;
		OneFigureStep(board, size, figure, ln, col);
	}
}

void Bishop(Mat board, const Coor &size, Figure &figure)
{
	OneFigureStep(board, size, figure, -1, -1);
	OneFigureStep(board, size, figure, -1, 1);
	OneFigureStep(board, size, figure, 1, 1);
	OneFigureStep(board, size, figure, 1, -1);
}

void Rook(Mat board, const Coor &size, Figure &figure)
{
	OneFigureStep(board, size, figure, -1, 0);
	OneFigureStep(board, size, figure, 0, -1);
	OneFigureStep(board, size, figure, 0, 1);
	OneFigureStep(board, size, figure, 1, 0);
}

void Knight(Mat board, const Coor &size, Figure &figure)
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

void Filling(Mat board, const Coor &size, Figures &figures)
{
	for (Figures::iterator it = figures.begin(); it != figures.end(); it++)
		board[it->ln][it->col] = it->val;
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

void kingStep(std::queue<Coor> &kill, std::queue<Coor> &wave, Mat board, Coor &start, Coor &shift)
{
	Coor newPos(start.ln + shift.ln, start.col + shift.col);
	if (board[newPos.ln][newPos.col] > -4 && board[newPos.ln][newPos.col] <= 0)
	{
		if (board[newPos.ln][newPos.col] == 0)
			wave.push(newPos);
		else
			kill.push(newPos);
		board[newPos.ln][newPos.col] = board[start.ln][start.col] + 1;
	}
}

int Func(Coor &size, Figures figures, Coor start)
{
	if (figures.empty())
		return 0;

	Mat board;
	for (int i = 0; i < size.ln; i++)
		for (int j = 0; j < size.col; j++)
			if (i == 0 || j == 0 || i == size.ln - 1 || j == size.col - 1)
				board[i][j] = -4;
			else
				board[i][j] = 0;
	Filling(board, size, figures);

	std::queue<Coor> kill;
	std::queue<Coor> wave;
	wave.push(start);
	while (!wave.empty())
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

	int min = -1;
	while (!kill.empty())
	{
		Coor tempKill = kill.front();
		kill.pop();
		Figures tempFigures = figures;
		for (Figures::iterator it = tempFigures.begin(); it != tempFigures.end(); it++)
		{
			if (it->ln == tempKill.ln && it->col == tempKill.col)
			{
				tempFigures.erase(it);
				break;
			}
		}
		int temp = Func(size, tempFigures, tempKill);
		if (temp >= 0)
		{
			if (min < 0 || temp + board[tempKill.ln][tempKill.col] < min)
				min = temp + board[tempKill.ln][tempKill.col];
		}
	}
	return min;
}

int main()
{
	std::ifstream fin("04", std::ios_base::in);

	Coor size;
	fin >> size.ln >> size.col;
	fin.get();

	char ch;
	Figures figures;
	
	Coor start;
	for (int i = 0; i < size.ln; i++)
	{
		for (int j = 0; j < size.col; j++)
		{
			int val = 0;
			ch = fin.get();
			if (ch == '*')
			{
				start.ln = i + 1;
				start.col = j + 1;
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
	size.ln += 2;
	size.col += 2;

	int temp = Func(size, figures, start);
	std::ofstream fout("output.txt", std::ios_base::out | std::ios_base::trunc);
	fout << temp;
	return 0;
}