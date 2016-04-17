// Test-Driven-Development.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../LifeOnMars/LifeOnMars.h"
#include <boost/test/floating_point_comparison.hpp>


bool IsFilesEqual(std::string const& fileName1, std::string const& fileName2)
{
	auto command = "fc " + fileName1 + " " + fileName2;
	return !system(command.c_str());
}

bool IsProgramWorkCorrect(CGraph & graph, std::string const& inName, std::string const& outName, std::string const& ethalonOutName, const long maxTime = 2000)
{
	auto time = RunProgram(graph, inName, outName);
	return IsFilesEqual(outName, ethalonOutName) && time < maxTime;
}


BOOST_AUTO_TEST_SUITE(LifeOnMars_test)

	struct Fixture
	{
		Fixture()
		{

		}

		~Fixture()
		{

		}

		CGraph m_graph;

		bool RunTest(std::string const& inName, std::string const& outName, std::string const& ethalonName)
		{
			return IsProgramWorkCorrect(m_graph, "tests\\input\\" + inName, "tests\\output\\" + outName,
				"tests\\ethalon\\" + ethalonName);
		}
	};


	BOOST_FIXTURE_TEST_CASE(small_file, Fixture)
	{
		BOOST_CHECK(RunTest("input1.txt", "output1.txt", "output1.txt"));
		BOOST_CHECK(RunTest("input2.txt", "output2.txt", "output2.txt"));
		BOOST_CHECK(RunTest("input3.txt", "output3.txt", "output3.txt"));
	}

BOOST_AUTO_TEST_SUITE_END()
