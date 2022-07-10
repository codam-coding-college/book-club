#include "parser_string.hpp"
#include <cstring>
#include <iostream>

namespace json_parse {

// invariant: first character in stream is '"'
Parser::ParseResult ParserString::parse(InputStream& is) {
	is.ignore();
	for (char ch; is.get(ch);) {
		if (ch == '"') {
			std::cout << "Result:" << str << '\n';
			return ParseResult::Done;
		}
		str.push_back(ch);
	}
	return ParseResult::Error;
}

Json ParserString::finish() {
	return Json { str };
}

}
