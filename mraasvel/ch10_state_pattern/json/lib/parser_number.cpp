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
	// [-][1-9]\d*[.\d+][e | E -+ \d+]
	// has to be 5 due to null terminator
	static constexpr char regex[] = R"(-?[1-9]\d*[.\d+]?[eE])";
	std::string str;
	if (is.peek() == '-') {
		str.push_back(is.get());
	}
	while (isdigit(is.peek())) {
		str.push_back(is.get());
	}
	n = std::stoi(str);
	return ParseResult::Done;
}

Json ParserNumber::finish() {
	return Json { n };
}

}
