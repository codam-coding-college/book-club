//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../tests/jsons/nulltype/";

TEST_CASE("null", "[nulltype tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "null.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::NULL_TYPE);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("null_with_newline", "[nulltype tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "null_with_newline.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::NULL_TYPE);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("nul", "[nulltype tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "nul.json");
		auto node = parser.parse();
		(void)node;
		REQUIRE(false);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cout << "exception: " << e.what() << "\n";
		std::string errmsg = e.what();
		REQUIRE(errmsg.find("Invalid nulltype") != std::string::npos);
	}
}

TEST_CASE("nil", "[nulltype tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "nil.json");
		auto node = parser.parse();
		(void)node;
		REQUIRE(false);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cout << "exception: " << e.what() << "\n";
		std::string errmsg = e.what();
		REQUIRE(errmsg.find("Invalid nulltype") != std::string::npos);
	}
}
