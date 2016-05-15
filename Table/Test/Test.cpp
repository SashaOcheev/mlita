// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../Table/Table.h"

const long MAX_TIME = 2000;

bool IsFilesEqual(std::string const& fileName1, std::string const& fileName2)
{
	auto command = "fc " + fileName1 + " " + fileName2;
	return !system(command.c_str());
}

long MeasureRunProgramTime(const std::string &inName, const std::string &outName)
{
	auto start = std::clock();
	CTable table(inName);
	table.FillTable();
	table.PrintNullLineToFile(outName);
	return std::clock() - start;
}

bool IsProgramWorkCorrect(const std::string &inName, const std::string outName, const std::string expectedFileName, const long maxTime = MAX_TIME)
{
	auto time = MeasureRunProgramTime(inName, outName);
	return IsFilesEqual(outName, expectedFileName) && time < maxTime;
}

bool RunTest(const std::string &inName, const std::string outName, const std::string expectedFileName)
{
	return IsProgramWorkCorrect("tests\\input\\" + inName, "tests\\output\\" + outName, "tests\\expected\\" + expectedFileName);
}


BOOST_AUTO_TEST_SUITE(Name_tests)

	BOOST_AUTO_TEST_CASE(test_from_example)
	{
		BOOST_CHECK(RunTest("input1.txt", "output1.txt", "output1.txt"));
	}

	BOOST_AUTO_TEST_CASE(test_2x2_divider_4)
	{
		BOOST_CHECK(RunTest("input2.txt", "output2.txt", "output2.txt"));
	}

	BOOST_AUTO_TEST_CASE(test_3x3)
	{
		BOOST_CHECK(RunTest("input3.txt", "output3.txt", "output3.txt"));
	}

	BOOST_AUTO_TEST_CASE(test_6x3)
	{
		BOOST_CHECK(RunTest("input4.txt", "output4.txt", "output4.txt"));
	}

	BOOST_AUTO_TEST_CASE(test_5x5)
	{
		BOOST_CHECK(RunTest("input5.txt", "output5.txt", "output5.txt"));
	}

	BOOST_AUTO_TEST_CASE(test_5x10_divider_3)
	{
		BOOST_CHECK(RunTest("input6.txt", "output6.txt", "output6.txt"));
	}

	BOOST_AUTO_TEST_CASE(test_10x10_divider_2)
	{
		BOOST_CHECK(RunTest("input7.txt", "output7.txt", "output7.txt"));
	}

	BOOST_AUTO_TEST_CASE(zero_repeated_test_2000x2000_divider_1000000000)
	{
		BOOST_CHECK(RunTest("input8.txt", "output8.txt", "output8.txt"));
	}

	BOOST_AUTO_TEST_CASE(max_random_test)
	{
		BOOST_CHECK(RunTest("input9.txt", "output9.txt", "output9.txt"));
	}

BOOST_AUTO_TEST_SUITE_END()


