// MultiplicationGame.cpp : Defines the entry point for the console application.
//

//15.2.���� � ���������(6)
//
//���� ������ � ���������: �������� ����� ����� P �� ���� �� ����� �� 2 �� 5.
//������ ����� ������ �������� � P = 1, ������ ���������, ����� ����� ��������
//������ �����, ����� ������ � �.�. ����� ������� ���� �� ������ ����� N, �
//����������� ��������� ���, ��� ������ �������� ������� P ? N. ����������, ���
//�������� ��� �������� N, ���� ��� ������ ��������� �������.
//
//����������� : 2 <= N <= 10000, ����� 1 �.
//
//���� �� ����� INPUT.TXT
//� ������ ������ ��������� ���������� ������ M. � ��������� M ������� ��������
//�������� N ��� ������ ������.
//
//����� � ���� OUTPUT.TXT
//��������� � ����� � ������� 1 � ���� ������� ������ �����, ��� 2 - ���� �������
//������.


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

