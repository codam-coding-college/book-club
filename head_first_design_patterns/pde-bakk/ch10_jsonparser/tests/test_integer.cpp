//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"
#include <climits>

static std::string	TEST_FOLDER = "../../tests/jsons/int/";

TEST_CASE("42", "[list tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "42.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::INTEGER);
		int integer = node->returnInt();
		REQUIRE(integer == 42);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("-42", "[list tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "neg42.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::INTEGER);
		int integer = node->returnInt();
		REQUIRE(integer == -42);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("zero", "[list tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "zero.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::INTEGER);
		int integer = node->returnInt();
		REQUIRE(integer == 0);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("int_max", "[list tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "int_max.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::INTEGER);
		int integer = node->returnInt();
		REQUIRE(integer == INT_MAX);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("int_min", "[list tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "int_min.json");
		auto node = parser.parse();
		REQUIRE(node->getType() == e_type::INTEGER);
		int integer = node->returnInt();
		REQUIRE(integer == INT_MIN);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}
