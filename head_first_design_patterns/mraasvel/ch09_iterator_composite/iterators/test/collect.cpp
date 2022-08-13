#include "consumers.hpp"
#include "range_iterator.hpp"
#include "map.hpp"
#include <catch2/catch.hpp>

using namespace Maarten;
using std::vector;

TEST_CASE("collect") {
	Map<RangeIterator<int>, int> map {
		RangeIterator<int> { 1, 5},
		[] (int n) { return n * 2; }
	};
	auto result = collect(map);
	vector<int> expected { 2, 4, 6, 8 };
	REQUIRE(result == expected);
}
