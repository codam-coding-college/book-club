//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../../tests/jsons/string/";

TEST_CASE("test_string", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "abi.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::STRING);
		std::string str = node->returnString();
		REQUIRE(str == "abi");
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}
