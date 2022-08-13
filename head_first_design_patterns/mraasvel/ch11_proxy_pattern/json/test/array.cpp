#include "json.hpp"
#include "json_parse.hpp"
#include <catch2/catch.hpp>
#include <sstream>

using json::Json;

TEST_CASE("array_null") {
	std::stringstream ss { "[null, null, null]" };
	Json json = json_parse::parse(ss);

	Json::ArrayType array;
	array.emplace_back(std::unique_ptr<Json> { new Json {} });
	array.emplace_back(std::unique_ptr<Json> { new Json {} });
	array.emplace_back(std::unique_ptr<Json> { new Json {} });
	Json expected { std::move(array) };
	REQUIRE(json == expected);
}
