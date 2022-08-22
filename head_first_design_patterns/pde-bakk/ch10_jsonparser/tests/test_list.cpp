//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../tests/jsons/list/";

TEST_CASE("list_small", "[list tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "list_small.json");
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

TEST_CASE("list_empty", "[list tests]") {
	try {
		JsonParser	parser( TEST_FOLDER + "list_empty.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::LIST);
		auto list = node->returnList();
		REQUIRE(list.size() == 0);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("list_complex", "[list tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "list_complex.json");
		auto node = parser.parse();
		std::cout << *node << "\n\n";
		REQUIRE(node->getType() == e_type::LIST);
		auto list = node->returnList();
		REQUIRE(list.size() == 5);
		REQUIRE(list[0]->getType() == e_type::LIST);
		REQUIRE(list[1]->getType() == e_type::OBJECT);
		REQUIRE(list[2]->getType() == e_type::BOOLEAN);
		REQUIRE(list[3]->getType() == e_type::NULL_TYPE);
		REQUIRE(list[4]->getType() == e_type::LIST);

		auto firstItem = list[0]->returnList();
		for (auto i : firstItem) {
			REQUIRE(i->getType() == e_type::INTEGER);
			REQUIRE(i->returnInt() == 42);
		}

		auto secondItem = list[1]->returnObject();
		REQUIRE(secondItem.empty());

		auto thirdItem = list[2]->returnBool();
		REQUIRE(thirdItem == true);

		// how and why would I return a nulltype for the fourth item?

		auto fifthItem = list[4]->returnList();
		REQUIRE(fifthItem.size() == 3);
		std::string	neefjes[3] = {"kwik", "kwek", "kwak"};
		for (size_t i = 0; i < fifthItem.size(); i++) {
			REQUIRE(fifthItem[i]->getType() == e_type::STRING);
			REQUIRE(fifthItem[i]->returnString() == neefjes[i]);
		}


	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}
