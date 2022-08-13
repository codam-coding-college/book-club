#include "consumers.hpp"
#include "range_iterator.hpp"
#include <catch2/catch.hpp>

using namespace Maarten;

int f(int acc, int n) {
	return acc + n;
}

TEST_CASE("fold") {
	RangeIterator<int> range { 1, 5 };

	{
		int sum = fold(0, range, [] (int acc, int n) { return acc + n; });
		int expected = 10;
		REQUIRE(sum == expected);
	}

	{
		int product = fold(1, range, [] (int acc, int n) { return acc * n; });
		int expected = 24;
		REQUIRE(product == expected);
	}
}
