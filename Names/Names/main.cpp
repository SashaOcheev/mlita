// Names.cpp : Defines the entry point for the console application.
//

//13.8 (8) Имена

#include "stdafx.h"
#include "Name.h"

int main()
{
	CName obj;
	obj.InitFromFile("input.txt");
	obj.RunAlgorithm();
	obj.PrintChildNameToFile("output.txt");

    return 0;
}

