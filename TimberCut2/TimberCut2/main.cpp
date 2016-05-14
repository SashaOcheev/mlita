// TimberCut2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TimberCount2.h"

#include <ctime>

/*14.10.������ ����� 2 (9)
�� �������� �������� ���� ������ L ������.��������� ������� N ��������.������� �����
���� �� �����, ����� ������� ���������� ������������ �������.��������� ������ �������
����� ����� �������������� �����.���������� ����������� ��������� �������.

����.� ������ ������ ���������� ����� ������ ����������� ����� L(2 <= L <= 10^5) � N(N < L) �
����� ����� � ����� ��������.

�����.� ������������ ������ ������� ����������� ��������� ��������.*/


int main()
{
	std::ifstream input("input.txt");
	unsigned length, timberCount;
	input >> length >> timberCount;

	std::ofstream output("output.txt");
	output << MinCost(length, timberCount) << std::endl;

	return 0;
}