#include "json_parse.hpp"
#include <sstream>
#include <catch2/catch.hpp>

using json::Json;

TEST_CASE("number") {
	Json expected { -12345 };
	std::stringstream ss { "-12345" };
	Json result = json_parse::parse(ss);
	REQUIRE(result == expected);
}
