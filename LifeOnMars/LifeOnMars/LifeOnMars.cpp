// LifeOnMars.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LifeOnMars.h"

int SqrOfDist(int x, int y)
{
	return (x - y) * (x - y);
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

	int currentDist = 0;
	size_t compCount = m_count;
	for (size_t i = 0; compCount > m_limit; i++)
	{
		auto firstCompNumb = m_verticies[m_edges[i].first].compNumber;
		auto secondCompNumb = m_verticies[m_edges[i].second].compNumber;

		if (firstCompNumb != secondCompNumb)
		{
			compCount--;

			for (size_t j = 0; j < m_components[secondCompNumb].size(); j++)
			{
				m_verticies[m_edges[i].second].compNumber = firstCompNumb;
				m_verticies[m_components[secondCompNumb][j]].compNumber = firstCompNumb;
				m_components[firstCompNumb].push_back(m_components[secondCompNumb][j]);
			}

			m_components[secondCompNumb].clear();

			currentDist = m_edges[i].sqrDist;
		}
	}
	return sqrtf(static_cast<float>(currentDist) / speed);
}

void CGraph::ReadVerticies(std::istream & in)
{
	m_verticies.resize(m_count);
	m_components.resize(m_count);

	for (size_t i = 0; i < m_verticies.size(); i++)
	{
		int x, y;
		in >> x >> y;
		m_verticies[i].x = x;
		m_verticies[i].y = y;
		m_verticies[i].compNumber = i;

		m_components[i].push_back(i);
	}
}

void CGraph::InitEdges()
{
	m_edges.resize((m_verticies.size() * (m_verticies.size() - 1)) / 2);

	size_t number = 0;
	for (size_t i = 0; i < m_verticies.size() - 1; i++)
		for (size_t j = i + 1; j < m_verticies.size(); j++, number++)
		{
			m_edges[number].first = i;
			m_edges[number].second = j;
			m_edges[number].sqrDist =
				SqrOfDist(m_verticies[i].x, m_verticies[j].x) + SqrOfDist(m_verticies[i].y, m_verticies[j].y);
		}
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