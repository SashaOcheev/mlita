#include "stdafx.h"
#include "LifeOnMars.h"

/*
12.6. ����� �� ����� (8)
���� �� ����� INPUT.TXT. � ������ ������ �������� ����� ������ ��� ����� �������������
��������: ��������� ���������� ��������� N (1 ? N ? 1000), ����� K (1 ? K ? 10, K< N)
� �������� ����� ��������� L (1 ? L ? 100). ����� � ��������� N ������� ���������� �����
������ ����� ���������� ��������� Xi , Yi (-1000 ? Xi , Yi ? 1000) � ����������� �����.
*/

int main(int argc, char* argv[])
{
	CGraph graph;
	std::cout << RunProgram(graph, "input.txt", "output.txt") << std::endl;

	return 0;
}