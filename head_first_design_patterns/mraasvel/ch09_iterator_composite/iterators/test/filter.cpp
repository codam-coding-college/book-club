#include "filter.hpp"
#include "range_iterator.hpp"
#include <catch2/catch.hpp>

using Maarten::Filter;
using Maarten::RangeIterator;

TEST_CASE("filter") {
	int start = 1; int end = 100;
	Filter<RangeIterator<int>> filter {
		RangeIterator<int> { start, end }, [] (const int& x) { return x % 2 == 0; }
	};
	for (int i = start; i < end; i++) {
		if (i % 2 == 0) {
			auto item = filter.next();
			REQUIRE(item == i);
		}
	}
	REQUIRE(!filter.has_next());
}
