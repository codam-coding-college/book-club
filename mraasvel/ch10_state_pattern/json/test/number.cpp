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

TEST_CASE("number_array") {
	Json::ArrayType array;
	array.emplace_back(std::unique_ptr<Json> { new Json { -12345 } });
	array.emplace_back(std::unique_ptr<Json> { new Json { 0.0 } });
	array.emplace_back(std::unique_ptr<Json> { new Json { 100.0 } });
	array.emplace_back(std::unique_ptr<Json> { new Json { 1.234 } });
	Json expected { std::move(array) };
	std::stringstream ss { "[-12345, 0.0, 1.0e+2, 1.234]" };
	Json result = json_parse::parse(ss);
	result.print();
	REQUIRE(result == expected);
}
