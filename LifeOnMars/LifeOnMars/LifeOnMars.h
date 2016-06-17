#pragma once

#include "stdafx.h"


struct Vertex
{
	int x;
	int y;
	size_t compNumber;
};

struct Edge
{
	size_t first;
	size_t second;
	int sqrDist;
	bool isSetted = false;
};

class CGraph
{
public:

	void InitFromText(std::istream & in);
	float RunAlgorithm();
	bool NextStep();
	float GetResult();


	std::vector<Vertex> m_verticies;
	std::vector<Edge> m_edges;
	std::vector<std::vector<size_t> > m_components;

	size_t m_count;
	size_t m_limit;
	int m_speed;
private:

	void ReadVerticies(std::istream & in);
	void InitEdges();
	void SortEdges();

	int m_lastStepDist;
	int m_step;
};

void RunProgram(CGraph & graph, std::string const& inputFileName, std::string const& outputFileName);
int SqrOfDist(int x, int y);
