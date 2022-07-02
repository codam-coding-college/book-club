#include "consumers.hpp"
#include "range_iterator.hpp"
#include <catch2/catch.hpp>

using Maarten::RangeIterator;

int summation(int n) {
	return n * (n + 1) / 2;
}

TEST_CASE("sum") {
	RangeIterator<int> range { 1, 10 };
	int sum = Maarten::sum(range);
	REQUIRE(sum == summation(9));
}
