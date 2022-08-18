//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../../tests/jsons/string/";

TEST_CASE("test_string", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "test_list_small.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::LIST);
		auto list = node->returnList();
		REQUIRE(list.size() == 4);
		REQUIRE(list[0]->getType() == e_type::INTEGER);
		REQUIRE(list[1]->getType() == e_type::STRING);
		REQUIRE(list[2]->getType() == e_type::BOOLEAN);
		REQUIRE(list[3]->getType() == e_type::NULL_TYPE);

	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}
