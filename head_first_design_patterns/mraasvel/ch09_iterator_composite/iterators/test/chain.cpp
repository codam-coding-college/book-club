#include "chain.hpp"
#include "range_iterator.hpp"
#include "iterator.hpp"
#include <catch2/catch.hpp>
#include <vector>

using Maarten::Chain;
using Maarten::RangeIterator;
using Maarten::Maarterator;
using std::vector;

TEST_CASE("chain") {
	RangeIterator<int> range { 5, 100 };
	vector<int> v { 1, 2, 3, 4 };
	Maarterator<vector<int>::iterator> maarten { v.begin(), v.end() };

	Chain<
		Maarterator<vector<int>::iterator>,
		RangeIterator<int>
	> chain {
		maarten, range
	};

	for (int i = 1; i < 100; i++) {
		REQUIRE(chain.has_next());
		REQUIRE(i == chain.next());
	}
	REQUIRE(!chain.has_next());
}
