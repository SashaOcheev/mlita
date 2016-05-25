// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../MultiplicationGame/game.h"


bool IsProgramWorkCorrect(int inputData, int expectedResult, long maxTime = 1000)
{
	auto time = std::clock();
	auto result = CalculateWinner(inputData);
	time = std::clock() - time;
	return  result == expectedResult && time < maxTime;
}


BOOST_AUTO_TEST_SUITE(Game_tests)

	BOOST_AUTO_TEST_CASE(test0)
	{
		BOOST_CHECK(IsProgramWorkCorrect(17, 1));
	}

	BOOST_AUTO_TEST_CASE(test1)
	{
		BOOST_CHECK(IsProgramWorkCorrect(2, 1));
	}

	BOOST_AUTO_TEST_CASE(test2)
	{
		BOOST_CHECK(IsProgramWorkCorrect(3, 1));
	}

	BOOST_AUTO_TEST_CASE(test3)
	{
		BOOST_CHECK(IsProgramWorkCorrect(4, 1));
	}

	BOOST_AUTO_TEST_CASE(test4)
	{
		BOOST_CHECK(IsProgramWorkCorrect(5, 1));
	}

	BOOST_AUTO_TEST_CASE(test5)
	{
		BOOST_CHECK(IsProgramWorkCorrect(6, 2));
	}

	BOOST_AUTO_TEST_CASE(test6)
	{
		BOOST_CHECK(IsProgramWorkCorrect(7, 2));
	}

	BOOST_AUTO_TEST_CASE(test7)
	{
		BOOST_CHECK(IsProgramWorkCorrect(8, 2));
	}

	BOOST_AUTO_TEST_CASE(test8)
	{
		BOOST_CHECK(IsProgramWorkCorrect(9, 2));
	}

	BOOST_AUTO_TEST_CASE(test9)
	{
		BOOST_CHECK(IsProgramWorkCorrect(10, 2));
	}

	BOOST_AUTO_TEST_CASE(test10)
	{
		BOOST_CHECK(IsProgramWorkCorrect(11, 1));
	}

	BOOST_AUTO_TEST_CASE(test11)
	{
		BOOST_CHECK(IsProgramWorkCorrect(12, 1));
	}

	BOOST_AUTO_TEST_CASE(test12)
	{
		BOOST_CHECK(IsProgramWorkCorrect(15, 1));
	}

	BOOST_AUTO_TEST_CASE(test13)
	{
		BOOST_CHECK(IsProgramWorkCorrect(16, 1));
	}

	BOOST_AUTO_TEST_CASE(maxTest)
	{
		BOOST_CHECK(IsProgramWorkCorrect(10'000, 2));
	}

BOOST_AUTO_TEST_SUITE_END()

