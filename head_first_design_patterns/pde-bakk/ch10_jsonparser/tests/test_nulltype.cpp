//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../../tests/jsons/nulltype/";

TEST_CASE("test_nulltype", "[nulltype tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "test_nulltype.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::NULL_TYPE);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}
