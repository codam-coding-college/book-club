//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../tests/jsons/boolean/";

TEST_CASE("test_boolean_true", "[boolean tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "true.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::BOOLEAN);
		bool boolean = node->returnBool();
		REQUIRE(boolean == true);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("test_boolean_false", "[boolean tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "false.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::BOOLEAN);
		bool boolean = node->returnBool();
		REQUIRE(boolean == false);

	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("test_boolean_tru", "[boolean tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "tru.json");
		auto node = parser.parse();
		(void)node;
		REQUIRE(false);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		std::string errmsg = e.what();
		REQUIRE(errmsg.find("Invalid boolean") != std::string::npos);
	}
}
