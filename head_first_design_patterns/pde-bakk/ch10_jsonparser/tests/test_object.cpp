//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../tests/jsons/object/";

TEST_CASE("test_object", "[object tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "simple.json");
		auto node = parser.parseJSON();
		REQUIRE(node->getType() == e_type::OBJECT);
		auto& obj = node->returnObject();
		REQUIRE(obj.size() == 2);
		auto firstItem = obj.at("first");
		REQUIRE(firstItem->getType() == e_type::STRING);
		REQUIRE(firstItem->returnString() == "foo");
		auto secondItem = obj.at("second");
		REQUIRE(secondItem->getType() == e_type::STRING);
		REQUIRE(secondItem->returnString() == "bar");
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}
