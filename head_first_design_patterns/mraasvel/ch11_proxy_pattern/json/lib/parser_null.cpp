#include "parser_null.hpp"
#include <cstring>
#include <iostream>

namespace json_parse {

Parser::ParseResult ParserNull::parse(InputStream& is) {
	// has to be 5 due to null terminator
	char buf[5];
	is.get(buf, sizeof(buf));
	if (std::memcmp("null", buf, 4) != 0) {
		return ParseResult::Error;
	}
	return ParseResult::Done;
}

Json ParserNull::finish() {
	return Json {};
}

}
