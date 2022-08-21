//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"

static std::string	TEST_FOLDER = "../tests/jsons/string/";

TEST_CASE("abi_string", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "abi.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::STRING);
		std::string str = node->returnString();
		std::cout << str << "\n";
		REQUIRE(str == "abi");
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("contains_spaces", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "contains_spaces.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::STRING);
		std::string str = node->returnString();
		std::cout << "contains_spaces.json: \"" << str << "\"\n";
		REQUIRE(str == " martino ");
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("contains_tabs", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "contains_tabs.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::STRING);
		std::string str = node->returnString();
		std::cout << "contains_tabs.json: \"" << str << "\"\n";
		REQUIRE(str == "tabulations\t");
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("contains_newline", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "contains_newline.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::STRING);
		std::string str = node->returnString();
		std::cout << "contains_tabs.json: \"" << str << "\"\n";
		REQUIRE(str == "\n");
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("escape_characters", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "escape_characters.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::STRING);
		std::string str = node->returnString();
		std::cout << "escape_characters.json: \"" << str << "\"\n";
		REQUIRE(str == "foo\"bar\\tab");
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("invalid_backslash", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "invalid_backslash.json");
		auto node = parser.parse();
		REQUIRE(0 == 1);
		(void)node;
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(true);
	}
}

TEST_CASE("invalid_doublequote", "[string tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "invalid_doublequote.json");
		auto node = parser.parse();
		REQUIRE(0 == 1);
		(void)node;
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(true);
	}
}