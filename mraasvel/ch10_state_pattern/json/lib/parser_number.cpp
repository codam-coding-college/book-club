#include "parser_number.hpp"
#include <cstring>
#include <iostream>

namespace json_parse {

// number = [ minus ] int [ frac ] [ exp ]
// minus = "-"
// int = 1-9 \d*
// frac = "." \d+
// exp = "e" / "E" [ mins / plus ] \d+

Parser::ParseResult ParserNumber::parse(InputStream& is) {
	is >> d;
	if (is.fail()) {
		return ParseResult::Error;
	}
	return ParseResult::Done;
}

Json ParserNumber::finish() {
	return Json { d };
}

}
