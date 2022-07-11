#include "parser_string.hpp"
#include <cstring>
#include <iostream>

namespace json_parse {

// no escape character support
// no unicode support
Parser::ParseResult ParserString::parse(InputStream& is) {
	if (is.get() != '"') {
		return ParseResult::Error;
	}
	for (char ch; is.get(ch);) {
		if (ch == '"') {
			return ParseResult::Done;
		}
		str.push_back(ch);
	}
	return ParseResult::Error;
}

Json ParserString::finish() {
	auto json = Json { std::move(str) };
	str.clear();
	return json;
}

}
