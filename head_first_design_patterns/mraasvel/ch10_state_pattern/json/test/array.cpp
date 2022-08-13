#include "json.hpp"
#include "json_parse.hpp"
#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>

using json::Json;

TEST_CASE("array_null") {
	std::stringstream ss { "[  null , null,  null ]" };
	Json json = json_parse::parse(ss);

	Json::ArrayType array;
	array.emplace_back(std::unique_ptr<Json> { new Json {} });
	array.emplace_back(std::unique_ptr<Json> { new Json {} });
	array.emplace_back(std::unique_ptr<Json> { new Json {} });
	Json expected { std::move(array) };
	REQUIRE(json == expected);
}

TEST_CASE("weird_array") {
	std::stringstream ss { "[1234[]]]]" };
	try {
		Json json = json_parse::parse(ss);
		json.print(std::cout, true);
		REQUIRE(false); // expected failure
	} catch (std::exception& e) {
		REQUIRE(true);
	}
}
