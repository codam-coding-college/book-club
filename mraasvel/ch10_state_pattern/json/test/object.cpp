#include "json_parse.hpp"
#include <catch2/catch.hpp>
#include <sstream>

using json_parse::Json;

TEST_CASE("object") {
	std::stringstream ss {
		"{\n"
		"\t\"name\": null,\n"
		"\t\"key\": \"string value\"\n"
		"}"
	};

	Json::ObjectType object {};
	object["name"] = std::unique_ptr<Json>(new Json {});
	object["key"] = std::unique_ptr<Json>(new Json { std::string {"string value"} });
	Json expected { std::move(object) };

	auto result = json_parse::parse(ss);

	REQUIRE(result.get_type() == json::Type::Object);
	const auto& obj = result.get_object();
	REQUIRE(result == expected);
}

TEST_CASE("nested_object") {
	std::stringstream ss {
		"{"
			"\"object\": {"
				"\"key\": null"
			"},"
			"\"array\": [],"
			"\"array_two\": [null, null, \"key\"],"
			"\"array_three\": ["
				"[null],"
				"{},"
				"{ \"key\": \"value\" }"
			"]"
		"}"
	};

	auto result = json_parse::parse(ss);
	// result.print();
}
