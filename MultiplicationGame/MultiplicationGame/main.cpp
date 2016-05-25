// MultiplicationGame.cpp : Defines the entry point for the console application.
//

//15.2.Игра в умножение(6)
//
//Двое играют в умножение: умножают целое число P на одно из чисел от 2 до 5.
//Первый игрок всегда начинает с P = 1, делает умножение, затем число умножает
//второй игрок, снова первый и т.д. Перед началом игры им задают число N, и
//победителем считается тот, кто первым добьется условия P ? N. Определить, кто
//выиграет при заданном N, если оба играют наилучшим образом.
//
//Ограничения : 2 <= N <= 10000, время 1 с.
//
//Ввод из файла INPUT.TXT
//В первой строке находится количество партий M. В следующих M строках задаются
//значения N для каждой партии.
//
//Вывод в файл OUTPUT.TXT
//Выводится М строк с числами 1 – если победит первый игрок, или 2 - если победит
//второй.


#include "stdafx.h"
#include "game.h"

int main()
{
	std::ifstream input("input.txt");

	int partiesCount;
	int currentLimit;
	std::ofstream output("output.txt");

	input >> partiesCount;
	while (input >> currentLimit)
	{
		output << CalculateWinner(currentLimit) << std::endl;
	}

    return 0;
}

