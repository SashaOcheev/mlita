// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../Names/Name.h"
#include <ctime>


bool IsFilesEqual(std::string const& fileName1, std::string const& fileName2)
{
	auto command = "fc " + fileName1 + " " + fileName2;
	return !system(command.c_str());
}

long MeasureRunProgramTime(const std::string &inName, const std::string &outName)
{
	auto start = std::clock();
	CName name;
	name.InitFromFile(inName);
	name.RunAlgorithm();
	name.PrintChildNameToFile(outName);
	return std::clock() - start;
}

bool IsProgramWorkCorrect(const std::string &inName, const std::string outName, const std::string expectedFileName, const long maxTime = 2000)
{
	auto time = MeasureRunProgramTime(inName, outName);
	return IsFilesEqual(outName, expectedFileName) && time < maxTime;
}

bool RunTest(const std::string &inName, const std::string outName, const std::string expectedFileName)
{
	return IsProgramWorkCorrect("tests\\input\\" + inName, "tests\\output\\" + outName, "tests\\expected\\" + expectedFileName);
}


BOOST_AUTO_TEST_SUITE(Name_tests)

BOOST_AUTO_TEST_CASE(different_names_letters_test)
{
	BOOST_CHECK(RunTest("input1.txt", "output1.txt", "output1.txt"));
}

BOOST_AUTO_TEST_CASE(different_names_letters_loading_test)
{
	BOOST_CHECK(RunTest("input2.txt", "output2.txt", "output2.txt"));
}

BOOST_AUTO_TEST_CASE(same_names_test)
{
	BOOST_CHECK(RunTest("input3.txt", "output3.txt", "output3.txt"));
}

BOOST_AUTO_TEST_CASE(same_names_loading_test)
{
	BOOST_CHECK(RunTest("input4.txt", "output4.txt", "output4.txt"));
}

BOOST_AUTO_TEST_CASE(different_length_repeated_letter_test)
{
	BOOST_CHECK(RunTest("input5.txt", "output5.txt", "output5.txt"));
}

BOOST_AUTO_TEST_CASE(same_names_repeated_letter_loading_test)
{
	BOOST_CHECK(RunTest("input6.txt", "output6.txt", "output6.txt"));
}

BOOST_AUTO_TEST_CASE(test_from_example_1)
{
	BOOST_CHECK(RunTest("input7.txt", "output7.txt", "output7.txt"));
}

BOOST_AUTO_TEST_CASE(test_from_example_2)
{
	BOOST_CHECK(RunTest("input8.txt", "output8.txt", "output8.txt"));
}

BOOST_AUTO_TEST_CASE(ordinary_loading_test)
{
	BOOST_CHECK(RunTest("input9.txt", "output9.txt", "output9.txt"));
}


BOOST_AUTO_TEST_SUITE_END()

