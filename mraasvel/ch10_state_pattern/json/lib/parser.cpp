#include "parser.hpp"
#include <iostream>

namespace json_parse {

Parser::Parser(InputStream& is): is(is) {}

Json Parser::parse() {
	char c = is.get();
	std::cout << c << std::endl;
	return Json {};
}

}
