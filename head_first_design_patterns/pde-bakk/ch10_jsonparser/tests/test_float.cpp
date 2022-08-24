//
// Created by Peer De bakker on 8/18/22.
//

#include <catch2/catch.hpp>
#include "JsonParser.hpp"
#include <cmath>

static const float EPSILON = 0.00001;
static std::string	TEST_FOLDER = "../tests/jsons/float/";

static bool areSame(float a, float b) {
	return (fabs(a - b) < EPSILON);
}

TEST_CASE("pi", "[float tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "pi.json");
		auto node = parser.parseJSON();
		REQUIRE(node->getType() == e_type::FLOAT);
		float pi = node->returnFloat();
		std::cout << "pi = " << pi << "\n";
		REQUIRE(areSame(pi, 3.14159));
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("two", "[float tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "two.json");
		auto node = parser.parseJSON();
		REQUIRE(node->getType() == e_type::FLOAT);
		float pi = node->returnFloat();
		REQUIRE(areSame(pi, 2.05));
	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		REQUIRE(false);
	}
}

TEST_CASE("double_dot", "[float tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "double_dot.json");
		auto node = parser.parseJSON();
		(void)node;
		std::cout << *node;
		REQUIRE(false);
	} catch(std::exception& e) {
		// we shouldn't get here
		std::string errmsg = e.what();
		std::cerr << "exception: " << errmsg << "\n";
		REQUIRE(errmsg.find("Invalid float") != std::string::npos);
	}

	try {
		JsonParser	parser(TEST_FOLDER + "double_dot_2.json");
		auto node = parser.parseJSON();
		(void)node;
		std::cout << *node;
		REQUIRE(false);
	} catch(std::exception& e) {
		std::string errmsg = e.what();
		std::cerr << "exception: " << errmsg << "\n";
		REQUIRE(errmsg.find("Invalid float") != std::string::npos);
	}

}

TEST_CASE("many_dots", "[float tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "many_dots.json");
		auto node = parser.parseJSON();
		(void)node;
		std::cout << *node;
		REQUIRE(false);
	} catch(std::exception& e) {
		std::string errmsg = e.what();
		std::cerr << "exception: " << errmsg << "\n";
		REQUIRE(errmsg.find("Invalid float") != std::string::npos);
	}
}

TEST_CASE("dot_before", "[float tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "dot_before.json");
		auto node = parser.parseJSON();
		(void)node;
		REQUIRE(false);
	} catch(std::exception& e) {
		std::cerr << "exception: " << e.what() << "\n";
		std::string errmsg = e.what();
		REQUIRE(errmsg.find("Number: Invalid token") != std::string::npos);
	}
}

TEST_CASE("dot_after", "[float tests]") {
	try {
		JsonParser	parser(TEST_FOLDER + "dot_after.json");
		auto node = parser.parseJSON();
		(void)node;
		std::cout << typeToString(node->getType()) << ": " << *node;
		REQUIRE(false);
	} catch(std::exception& e) {
		std::string errmsg = e.what();
		std::cerr << "exception: " << errmsg << "\n";
		REQUIRE(errmsg.find("Invalid float") != std::string::npos);
	}
}
