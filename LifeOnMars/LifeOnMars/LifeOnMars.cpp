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
	m_speed = m_speed * m_speed * 4;
	m_lastStepDist = 0;
	m_minMaxX = m_minMaxY = { pow(10, 5), pow(-10, 5) };
	m_step = 0;
	ReadVerticies(in);

	InitEdges();
	SortEdges();
}

float CGraph::RunAlgorithm()
{
	while (NextStep())
	{
	}

	return GetResult();
}

bool CGraph::NextStep()
{
	auto firstCompNumb = m_verticies[m_edges[m_step].first].compNumber;
	auto secondCompNumb = m_verticies[m_edges[m_step].second].compNumber;

	if (firstCompNumb != secondCompNumb)
	{
		m_edges[m_step].isSetted = true;
		m_count--;

		for (size_t j = 0; j < m_components[secondCompNumb].size(); j++)
		{
			m_verticies[m_edges[m_step].second].compNumber = firstCompNumb;
			m_verticies[m_components[secondCompNumb][j]].compNumber = firstCompNumb;
			m_components[firstCompNumb].push_back(m_components[secondCompNumb][j]);
		}

		m_components[secondCompNumb].clear();

		m_lastStepDist = m_edges[m_step].sqrDist;
	}
	if (m_step < m_edges.size())
		currentEdge = { m_edges[m_step + 1].first, m_edges[m_step + 1].second };

	m_step++;
	return m_count > m_limit;
}

float CGraph::GetResult()
{
	return sqrtf(static_cast<float>(m_lastStepDist) / m_speed);
}

void CGraph::ReadVerticies(std::istream & in)
{
	m_verticies.resize(m_count);
	m_components.resize(m_count);

	for (size_t i = 0; i < m_verticies.size(); i++)
	{
		int x, y;
		in >> x >> y;

		SetMinMax(x, y);

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

void CGraph::SetMinMax(int x, int y)
{
	m_minMaxX.first = (x < m_minMaxX.first) ? x : m_minMaxX.first;
	m_minMaxX.second = (x > m_minMaxX.second) ? x : m_minMaxX.second;
	m_minMaxY.first = (y < m_minMaxY.first) ? y : m_minMaxY.first;
	m_minMaxY.second = (y > m_minMaxY.second) ? y : m_minMaxY.second;
}

void RunProgram(CGraph & graph, std::string const& inputFileName, std::string const& outputFileName)
{
	std::ifstream inputFile(inputFileName);

	graph.InitFromText(inputFile);
	auto res = graph.RunAlgorithm();

	std::ofstream outputFile(outputFileName);
	outputFile << std::fixed << std::setprecision(2) << res << std::endl;
}