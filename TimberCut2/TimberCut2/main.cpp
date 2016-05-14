// TimberCut2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TimberCount2.h"

#include <ctime>

/*14.10.–аспил бруса 2 (9)
Ќа пилораму привезли брус длиной L метров.“ребуетс€ сделать N распилов.–аспилы дел€т
брус на части, длина которых выражаетс€ натуральными числами.—тоимость одного распила
равна длине распиливаемого бруса.ќпределить минимальную стоимость распила.

¬вод.¬ первой строке содержатс€ через пробел натуральные числа L(2 <= L <= 10^5) и N(N < L) Ц
длина бруса и число распилов.

¬ывод.¬ единственной строке вывести минимальную стоимость распилов.*/


int main()
{
	std::ifstream input("input.txt");
	unsigned length, timberCount;
	input >> length >> timberCount;

	std::ofstream output("output.txt");
	output << MinCost(length, timberCount) << std::endl;

	return 0;
}