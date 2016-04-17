#include "stdafx.h"
#include "LifeOnMars.h"

/*
12.6. ∆изнь на ћарсе (8)
¬вод из файла INPUT.TXT. ¬ первой строке задаютс€ через пробел три целых положительных
значени€: начальное количество поселений N (1 ? N ? 1000), число K (1 ? K ? 10, K< N)
и скорость роста поселений L (1 ? L ? 100). ƒалее в следующих N строках содержатс€ через
пробел целые координаты поселений Xi , Yi (-1000 ? Xi , Yi ? 1000) в марсианских мил€х.
*/

int main(int argc, char* argv[])
{
	CGraph graph;
	std::cout << RunProgram(graph, "input.txt", "output.txt") << std::endl;

	return 0;
}