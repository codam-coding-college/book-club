#include "range_iterator.hpp"
#include <catch2/catch.hpp>

using Maarten::RangeIterator;

TEST_CASE("range") {
	int start = 1;
	int end = 100;
	RangeIterator<int> range {start, end};
	for (int i = start; i < end; i++) {
		REQUIRE(i == range.next());
	}
	REQUIRE(!range.has_next());
}

TEST_CASE("unbounded") {
	RangeIterator<int> range {1};
	for (int i = 1; i < 100; i++) {
		REQUIRE(i == range.next());
	}
	REQUIRE(range.has_next());
}
