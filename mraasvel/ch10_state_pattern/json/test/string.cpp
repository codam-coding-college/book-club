#include "json_parse.hpp"
#include <catch2/catch.hpp>
#include <sstream>

using json_parse::Json;

TEST_CASE("string") {
	std::string str { "this is a string" };
	std::stringstream ss;
	ss << '"' << str << '"';
	auto json = json_parse::parse(ss);
	Json expected { str };
	REQUIRE(json == expected);
}
