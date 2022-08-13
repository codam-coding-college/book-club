#include "take.hpp"
#include "range_iterator.hpp"
#include <catch2/catch.hpp>

using Maarten::Take;
using Maarten::RangeIterator;

TEST_CASE("take") {
	RangeIterator<int> range { 1 }; // unbounded range
	Take<RangeIterator<int>> take { 5, range }; // only take 5
	for (int i = 1; i <= 5; i++) {
		REQUIRE(take.has_next());
		REQUIRE(take.next() == i);
	}
	REQUIRE(!take.has_next());
}
