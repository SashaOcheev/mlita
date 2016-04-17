#pragma once

#include "stdafx.h"


struct Vertex
{
	int x;
	int y;
	std::shared_ptr<size_t> ptrTag;

	Vertex() = default;

	Vertex(int X, int Y, size_t tag);
};

struct Edge
{
	std::shared_ptr<Vertex> ptrFirst;
	std::shared_ptr<Vertex> ptrSecond;
	long sqrDist;

	Edge() = default;

	Edge(std::shared_ptr<Vertex> const& First, std::shared_ptr<Vertex> const& Second);
};

class CGraph
{
public:

	void InitFromText(std::istream & in);
	float RunAlgorithm();

private:

	void ReadVerticies(std::istream & in);
	void InitEdges();
	void SortEdges();

	std::vector<std::shared_ptr<Vertex> > m_verticies;
	std::vector<Edge> m_edges;

	size_t m_count;
	size_t m_limit;
	int m_speed;
};

void RunProgram(CGraph & graph, std::string const& inputFileName, std::string const& outputFileName);
long SqrOfDist(int x, int y);
