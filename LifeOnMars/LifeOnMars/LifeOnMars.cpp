// LifeOnMars.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LifeOnMars.h"

long SqrOfDist(int x, int y)
{
	return (x - y) * (x - y);
};


Vertex::Vertex(int X, int Y, size_t tag)
{
	x = X;
	y = Y;
	ptrTag = std::make_shared<size_t>(tag);
}

Edge::Edge(std::shared_ptr<Vertex> const& First, std::shared_ptr<Vertex> const& Second)
{
	ptrFirst = First;
	ptrSecond = Second;
	sqrDist = SqrOfDist(ptrFirst->x, ptrSecond->x) + SqrOfDist(ptrFirst->y, ptrSecond->y);
};


void CGraph::InitFromText(std::istream & in)
{
	in >> m_count >> m_limit >> m_speed;
	ReadVerticies(in);

	InitEdges();
	SortEdges();
}

float CGraph::RunAlgorithm()
{
	int speed = m_speed * m_speed * 4;

	float currentTime = 0.f;
	size_t compCount = m_count;
	for (size_t i = 0; compCount > m_limit; i++)
	{
		if (m_edges[i].ptrFirst->ptrTag != m_edges[i].ptrSecond->ptrTag)
		{
			compCount--;
			m_edges[i].ptrSecond->ptrTag = m_edges[i].ptrFirst->ptrTag;
			currentTime = static_cast<float>(m_edges[i].sqrDist) / static_cast<float>(speed);
		}
	}
	return sqrtf(currentTime);
}

void CGraph::ReadVerticies(std::istream & in)
{
	m_verticies.resize(m_count);

	for (size_t i = 0; i < m_verticies.size(); i++)
	{
		int x, y;
		in >> x >> y;
		m_verticies[i] = std::make_shared<Vertex>(x, y, i);
	}
}

void CGraph::InitEdges()
{
	m_edges.resize((m_verticies.size() * (m_verticies.size() - 1)) / 2);

	size_t number = 0;
	for (size_t i = 0; i < m_verticies.size() - 1; i++)
		for (size_t j = i + 1; j < m_verticies.size(); j++, number++)
			m_edges[number] = Edge(m_verticies[i], m_verticies[j]);
}

void CGraph::SortEdges()
{
	std::sort(m_edges.begin(), m_edges.end(),
		[](Edge const& first, Edge const& second)
	{
		return first.sqrDist < second.sqrDist;
	});
}

void RunProgram(CGraph & graph, std::string const& inputFileName, std::string const& outputFileName)
{
	std::ifstream inputFile(inputFileName);

	graph.InitFromText(inputFile);
	auto res = graph.RunAlgorithm();

	std::ofstream outputFile(outputFileName);
	outputFile << std::fixed << std::setprecision(2) << res << std::endl;
}