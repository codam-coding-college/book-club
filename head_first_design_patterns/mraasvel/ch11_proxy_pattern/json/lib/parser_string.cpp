#include "parser_string.hpp"
#include <cstring>
#include <iostream>

namespace json_parse {

// -1 on error
static int parse_escape(InputStream& is) {
	char c = is.get();
	switch (c) {
		case '"':
		case '\\':
		case '/':
			return c;
		case 'b':
			return '\b';
		case 'f':
			return '\f';
		case 'n':
			return '\n';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case 'u':
			throw ParseException { "unicode encoding not implemented" };
		default:
			return -1;
	}
}

// no escape character support
// no unicode support
Parser::ParseResult ParserString::parse(InputStream& is) {
	if (is.get() != '"') {
		return ParseResult::Error;
	}
	for (char ch; is.get(ch);) {
		switch (ch) {
			case '"':
				return ParseResult::Done;
			case '\\':
				{
					int escaped = parse_escape(is);
					if (escaped == -1) {
						return ParseResult::Error;
					}
					str.push_back(escaped);
				}
				break;
			default:
				if (!isprint(ch)) {
					return ParseResult::Error;
				}
				str.push_back(ch);
				break;
		}
	}
	return ParseResult::Error;
}

Json ParserString::finish() {
	auto json = Json { std::move(str) };
	str.clear();
	return json;
}

}
