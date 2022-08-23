//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../tests/jsons/";

TEST_CASE("test_empty", "[mix tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "empty.json");
		auto node = parser.parseJSON();
		REQUIRE(node == nullptr);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}
