
#include "stdafx.h"
#include "Name.h"

CName::CName()
{
	size_t size = 'z' - 'a' + 1;
	m_mother_letters_pos.resize(size);
	m_mother_pos = 0;
	m_father_letters_pos.resize(size);
	m_father_pos = 0;
}

void CName::InitFromFile(const std::string &fileName)
{
	std::ifstream file(fileName);
	InitLettersPos(file, m_mother_letters_pos);
	InitLettersPos(file, m_father_letters_pos);
}

	
void CName::RunAlgorithm()
{
	size_t i = m_mother_letters_pos.size();
	while (i > 0)
	{
		i--;

		size_t j = 0;
		while (j < m_mother_letters_pos[i].size() && m_mother_letters_pos[i][j] < m_mother_pos)
			j++;

		size_t k = 0;
		while (k < m_father_letters_pos[i].size() && m_father_letters_pos[i][k] < m_father_pos)
			k++;

		for (; j < m_mother_letters_pos[i].size() && k < m_father_letters_pos[i].size(); j++, k++)
		{
			m_child_name += static_cast<char>('a' + i);
			m_mother_pos = m_mother_letters_pos[i][j];
			m_father_pos = m_father_letters_pos[i][k];
		}
	}
}


void CName::PrintChildNameToFile(const std::string &fileName)
{
	std::ofstream file(fileName);
	if (!m_child_name.empty())
	{
		file << m_child_name << std::endl;
	}
}

void CName::InitLettersPos(std::ifstream &file, std::vector<std::vector<size_t> > &letters_pos)
{
	size_t i = 0;
	char ch;
	while (((ch = file.get()) <= 'z') && (ch >= 'a') && (!file.eof()))
	{
		letters_pos[ch - 'a'].push_back(i);
		i++;
	}
}