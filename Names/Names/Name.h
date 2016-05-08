#pragma once
#include "stdafx.h"

class CName
{
public:
	CName();
	void InitFromFile(const std::string &fileName);
	void RunAlgorithm();
	void PrintChildNameToFile(const std::string &fileName);


private:
	void InitLettersPos(std::ifstream &file, std::vector<std::vector<size_t> > &letters_pos);

	std::vector<std::vector<size_t> > m_mother_letters_pos;
	size_t m_mother_pos;
	std::vector<std::vector<size_t> > m_father_letters_pos;
	size_t m_father_pos;
	std::string m_child_name;
};