#include "json_parse.hpp"
#include <catch2/catch.hpp>
#include <sstream>

using json::Json;

TEST_CASE("bool_false") {
	std::stringstream ss { "false" };
	Json expected { false };
	Json result = json_parse::parse(ss);
	REQUIRE(result == expected);
}

TEST_CASE("bool_true") {
	std::stringstream ss { "true" };
	Json expected { true };
	Json result = json_parse::parse(ss);
	REQUIRE(result == expected);
}
