#include "permutations.hpp"
#include <catch2/catch.hpp>

using namespace Maarten;
using std::vector;

TEST_CASE("permutations") {
	Permutations<int> perm { vector<int> { 1, 2, 3 } };
	REQUIRE(vector<int> {1, 2, 3} == perm.next());
	REQUIRE(vector<int> {1, 3, 2} == perm.next());
	REQUIRE(vector<int> {2, 1, 3} == perm.next());
	REQUIRE(vector<int> {2, 3, 1} == perm.next());
	REQUIRE(vector<int> {3, 1, 2} == perm.next());
	REQUIRE(perm.has_next());
	REQUIRE(vector<int> {3, 2, 1} == perm.next());
	REQUIRE(!perm.has_next());
}
