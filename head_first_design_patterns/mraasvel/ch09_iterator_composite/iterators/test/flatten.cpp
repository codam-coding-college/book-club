#include "flatten.hpp"
#include "iterator.hpp"
#include <vector>
#include <catch2/catch.hpp>

using std::vector;
using Maarten::Maarterator;
using Maarten::Flatten;

using Nested = Maarterator<vector<int>::iterator>;
using TopLevel = Maarterator<vector<Nested>::iterator>;

TEST_CASE("flatten") {
	vector<int> v { 1, 2, 3, 4, 5 };
	vector<Nested> top {
		Nested { v.begin(), v.end() },
		Nested { v.begin(), v.end() },
		Nested { v.begin(), v.end() },
	};
	TopLevel it { top.begin(), top.end() };
	Flatten<TopLevel> flatten { it };
	vector<int> result;
	while (flatten.has_next()) {
		result.push_back(flatten.next());
	}
	vector<int> expected { v };
	expected.insert(expected.end(), v.begin(), v.end());
	expected.insert(expected.end(), v.begin(), v.end());
	REQUIRE(result == expected);
}
