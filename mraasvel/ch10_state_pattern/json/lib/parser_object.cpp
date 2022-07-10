#include "parser_object.hpp"
#include <cstring>
#include <iostream>
#include <cassert>

namespace json_parse {

Parser::ParseResult ParserObject::parse(InputStream& is) {
	char c = is.get();
	switch (c) {
		case '}':
			return ParseResult::Done;
		case '{':
			// check for empty array
			is >> std::ws;
			if (is.peek() == '}') {
				is.get();
				return ParseResult::Done;
			}
			return parse_name(is);
		case ',':
			return parse_name(is);
		default:
			return ParseResult::Error;
	}
}

Parser::ParseResult ParserObject::parse_name(InputStream& is) {
	is >> std::ws;
	if (string_parser.parse(is) == ParseResult::Error) {
		return ParseResult::Error;
	}
	is >> std::ws;
	if (is.get() != ':') {
		return ParseResult::Error;
	}
	return ParseResult::NextState;
}

Json ParserObject::finish() {
	return Json { std::move(object) };
}

void ParserObject::process_item(Json&& json) {
	auto name = string_parser.finish();
	auto type = json.get_type();
	object[name.get_string()] = std::unique_ptr<Json> { new Json { std::move(json) } };
}

}
