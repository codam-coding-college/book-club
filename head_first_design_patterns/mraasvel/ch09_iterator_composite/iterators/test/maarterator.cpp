#include "iterator.hpp"
#include <vector>
#include <catch2/catch.hpp>

using Maarten::Maarterator;
using std::vector;

TEST_CASE("maarten") {
	vector<int> v { 1, 2, 3, 4, 5 };
	Maarterator<vector<int>::iterator> maarten { v.begin(), v.end() };
	auto it = v.begin();
	while (maarten.has_next()) {
		REQUIRE(*it == maarten.next());
		it++;
	}
	REQUIRE(it == v.end());
}
