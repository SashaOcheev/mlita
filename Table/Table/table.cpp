
#include "stdafx.h"
#include "table.h"


CTable::CTable(const std::string &inputFileName)
{
	Reset();

	std::ifstream inFile(inputFileName);

	inFile >> m_lnCount >> m_colCount >> m_divider;

	std::vector<long long> zeroVec(m_colCount, 0);
	m_table.resize(MAX_SIZE, zeroVec);

	for (size_t i = 0; i < m_colCount; i++)
	{
		inFile >> m_table[0][i];
		m_table[0][i] %= m_divider;
	}
}

void CTable::Reset()
{
	m_colCount = m_lnCount = 0;
	m_divider = 1;
	m_table.clear();
}

void CTable::FillTable()
{
	for (size_t i = 1; i < m_lnCount; i++)
	{
		for (size_t j = MAX_SIZE - 1; j > 0; j--)
			m_table[j] = m_table[j - 1];

		for (size_t j = 0; j < m_colCount; j++)
		{
			m_table[0][j] = (m_table[1][j] +
				((i > 1) ? 2 : 1) * (((j == 0) ? 0 : m_table[1][j - 1]) + ((j == m_colCount - 1) ? 0 : m_table[1][j + 1])) -
				((j == 0 || j == m_colCount - 1) ? 0 : m_table[2][j]) * ((i == 2) ? 1 : 2)) %
				m_divider;

			if (m_table[0][j] < 0)
				m_table[0][j] = m_divider + m_table[0][j];
		}
	}
}


void CTable::PrintNullLineToFile(const std::string &outputFileName)
{
	std::ofstream outFile(outputFileName);
	for (size_t i = 0; i + 1 < m_colCount; i++)
	{
		outFile << m_table[0][i] << ' ';
	}
	outFile << m_table[0][m_colCount - 1] << std::endl;
}