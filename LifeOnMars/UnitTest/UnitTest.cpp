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

long MeasureRunProgramTime(CGraph & graph, std::string const& inName, std::string const& outName)
{
	auto start = std::clock();
	RunProgram(graph, inName, outName);
	return std::clock() - start;
}

bool IsProgramWorkCorrect(CGraph & graph, std::string const& inName, std::string const& outName, std::string const& ethalonOutName, const long maxTime = 2000)
{
	auto time = MeasureRunProgramTime(graph, inName, outName);
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


	BOOST_FIXTURE_TEST_CASE(count_of_cities_is_less_than_desired, Fixture)
	{
		BOOST_CHECK(RunTest("input1.txt", "output1.txt", "output1.txt"));
	}

	BOOST_FIXTURE_TEST_CASE(count_of_cities_is_equal_desired, Fixture)
	{
		BOOST_CHECK(RunTest("input2.txt", "output2.txt", "output2.txt"));
	}

	BOOST_FIXTURE_TEST_CASE(normal_test_1, Fixture)
	{
		BOOST_CHECK(RunTest("input3.txt", "output3.txt", "output3.txt"));
	}

	BOOST_FIXTURE_TEST_CASE(normal_test_2, Fixture)
	{
		BOOST_CHECK(RunTest("input4.txt", "output4.txt", "output4.txt"));
	}

	BOOST_FIXTURE_TEST_CASE(big_test, Fixture)
	{
		BOOST_CHECK(RunTest("input5.txt", "output5.txt", "output5.txt"));
	}

	BOOST_FIXTURE_TEST_CASE(biggest_test, Fixture)
	{
		BOOST_CHECK(RunTest("input6.txt", "output6.txt", "output6.txt"));
	}

	BOOST_FIXTURE_TEST_CASE(inp_7, Fixture)
	{
		BOOST_CHECK(RunTest("input7.txt", "output7.txt", "output7.txt"));
	}

	BOOST_FIXTURE_TEST_CASE(inp_8, Fixture)
	{
		BOOST_CHECK(RunTest("input8.txt", "output8.txt", "output8.txt"));
	}

BOOST_AUTO_TEST_SUITE_END()
