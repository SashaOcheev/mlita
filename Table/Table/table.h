#pragma once

class CTable
{
public:
	CTable(const std::string &inputFileName);
	void FillTable();
	void PrintNullLineToFile(const std::string &outputFileName);

private:
	void Reset();

	std::vector<std::vector<long long> > m_table;
	int m_divider;
	size_t m_lnCount;
	size_t m_colCount;
	const size_t MAX_SIZE = 3;
};
