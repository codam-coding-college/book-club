#include "json_parse.hpp"
#include <sstream>
#include <catch2/catch.hpp>

TEST_CASE("null") {
	std::stringstream ss { "  \nnull\n\t\n" };
	auto json = json_parse::parse(ss);
	REQUIRE(json.get_type() == json_parse::JsonType::Null);
}

TEST_CASE("null_invalid") {
	std::array<std::string, 4> inputs {
		"",
		"n",
		"n u l l",
		"nul\nl",
	};
	for (const std::string& s: inputs) {
		SECTION(s) {
			std::stringstream ss { s };
			try {
				auto json = json_parse::parse(ss);
				REQUIRE(false);
			} catch (std::exception& e) {
				REQUIRE(true);
			}
		}
	}
}
