#include "map.hpp"
#include "range_iterator.hpp"
#include <catch2/catch.hpp>

using Maarten::RangeIterator;
using Maarten::Map;

int map_function(int n) {
	return n * 2;
}

TEST_CASE("map") {
	int start = 1; int end = 100;
	RangeIterator<int> range { start, end };

	// can use a function pointer
	Map<RangeIterator<int>, int> map { range, map_function };

	for (int i = start; i < end; i++) {
		REQUIRE(map.next() == i * 2);
	}
	REQUIRE(!map.has_next());
}

TEST_CASE("other type") {
	int start = 1; int end = 100;
	Map<RangeIterator<int>, std::string> map {
		RangeIterator<int> { start, end },
		// can also use a lambda expression (anonymous/nameless function)
		[] (int n) { return std::to_string(n); }
	};
	for (int i = start; i < end; i++) {
		REQUIRE(map.next() == std::to_string(i));
	}
	REQUIRE(!map.has_next());
}
