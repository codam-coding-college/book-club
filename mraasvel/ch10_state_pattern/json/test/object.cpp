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

	Json::ObjectType object;
	object["key"] = std::unique_ptr<Json> { new Json {} };
	Json::ArrayType array;
	Json::ArrayType array_two;
	array_two.emplace_back(std::unique_ptr<Json> { new Json {} });
	array_two.emplace_back(std::unique_ptr<Json> { new Json {} });
	array_two.emplace_back(std::unique_ptr<Json> { new Json { std::string("key") } });

	Json::ArrayType a;
	a.emplace_back(std::unique_ptr<Json> { new Json {} });
	Json::ObjectType b;
	b["key"] = std::unique_ptr<Json> { new Json { std::string("value") } };
	Json::ArrayType array_three;
	array_three.emplace_back(std::unique_ptr<Json> { new Json { std::move(a) }});
	array_three.emplace_back(std::unique_ptr<Json> { new Json { Json::ObjectType {} }});
	array_three.emplace_back(std::unique_ptr<Json> { new Json { std::move(b) }});

	Json::ObjectType top;
	top["object"] = std::unique_ptr<Json> { new Json { std::move(object) } };
	top["array"] = std::unique_ptr<Json> { new Json { std::move(array) } };
	top["array_two"] = std::unique_ptr<Json> { new Json { std::move(array_two) } };
	top["array_three"] = std::unique_ptr<Json> { new Json { std::move(array_three) } };

	auto expected = Json { std::move(top) };
	auto result = json_parse::parse(ss);
	REQUIRE(result == expected);
}
