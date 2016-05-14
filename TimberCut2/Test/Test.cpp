// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../TimberCut2/TimberCount2.h"
#include <ctime>

bool IsProgramWorkCorrect(unsigned length, unsigned timberCount, unsigned expectedResult, long maxTime = 2000)
{
	auto start = std::clock();
	auto res = MinCost(length, timberCount);
	return (res == expectedResult) && ((std::clock() - start) <= maxTime);
}

bool IsInTime(unsigned length, unsigned timberCount, long maxTime = 2000)
{
	auto time = std::clock();
	MinCost(length, timberCount);
	return (std::clock() - time) < maxTime;
}

BOOST_AUTO_TEST_SUITE(TimberCount2_tests)

	BOOST_AUTO_TEST_CASE(test_from_example_1)
	{
		BOOST_CHECK(IsProgramWorkCorrect(10, 4, 18));
	}

	BOOST_AUTO_TEST_CASE(test_from_example_2)
	{
		BOOST_CHECK(IsProgramWorkCorrect(100, 3, 105));
	}

	BOOST_AUTO_TEST_CASE(test_3)
	{
		BOOST_CHECK(IsProgramWorkCorrect(7, 5, 18));
	}

	BOOST_AUTO_TEST_CASE(test_4)
	{
		BOOST_CHECK(IsProgramWorkCorrect(8, 6, 22));
	}

	BOOST_AUTO_TEST_CASE(test_5)
	{
		BOOST_CHECK(IsProgramWorkCorrect(8, 5, 20));
	}

	BOOST_AUTO_TEST_CASE(test_6)
	{
		BOOST_CHECK(IsProgramWorkCorrect(7, 4, 15));
	}

	BOOST_AUTO_TEST_CASE(test_7)
	{
		BOOST_CHECK(IsProgramWorkCorrect(6, 4, 14));
	}

	BOOST_AUTO_TEST_CASE(test_8)
	{
		BOOST_CHECK(IsProgramWorkCorrect(5, 3, 10));
	}

	BOOST_AUTO_TEST_CASE(test_9)
	{
		BOOST_CHECK(IsProgramWorkCorrect(10, 6, 26));
	}

	BOOST_AUTO_TEST_CASE(test_10)
	{
		BOOST_CHECK(IsProgramWorkCorrect(10, 7, 29));
	}

	BOOST_AUTO_TEST_CASE(test_11)
	{
		BOOST_CHECK(IsProgramWorkCorrect(10, 8, 32));
	}

	BOOST_AUTO_TEST_CASE(cunning_test)
	{
		BOOST_CHECK(IsProgramWorkCorrect(12, 9, 39));
	}

	BOOST_AUTO_TEST_CASE(max_test_1)
	{
		BOOST_CHECK(IsProgramWorkCorrect(100'000, 10, 100'034));
	}

	BOOST_AUTO_TEST_CASE(max_test_2)
	{
		BOOST_CHECK(IsInTime(100'000, 10'000));
	}

	BOOST_AUTO_TEST_CASE(max_test_3)
	{
		BOOST_CHECK(IsInTime(100'000, 30'000));
	}

	BOOST_AUTO_TEST_CASE(max_test_4)
	{
		BOOST_CHECK(IsInTime(100'000, 50'000));
	}

	BOOST_AUTO_TEST_CASE(max_test_6)
	{
		BOOST_CHECK(IsInTime(100'000, 70'000));
	}

	BOOST_AUTO_TEST_CASE(max_test_7)
	{
		BOOST_CHECK(IsInTime(100'000, 90'000));
	}

	BOOST_AUTO_TEST_CASE(max_test_8)
	{
		BOOST_CHECK(IsInTime(100'000, 99'999));
	}

BOOST_AUTO_TEST_SUITE_END()



