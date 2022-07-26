#include "parser_object.hpp"
#include <cstring>
#include <iostream>
#include <cassert>

namespace json_parse {

ParserObject::ParserObject(): started(false) {}

Parser::ParseResult ParserObject::parse(InputStream& is) {
	if (!started) {
		assert(is.get() == '{');
		skipws(is);
	}
	switch (is.peek()) {
		case '}':
			is.ignore();
			return ParseResult::Done;
		case ',':
			is.ignore();
			return parse_name(is);
		default:
			if (!started) {
				started = true;
				return parse_name(is);
			}
			return ParseResult::Error;
	}
}

Parser::ParseResult ParserObject::parse_name(InputStream& is) {
	skipws(is);
	if (string_parser.parse(is) == ParseResult::Error) {
		return ParseResult::Error;
	}
	skipws(is);
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
	auto result = object.insert(std::make_pair(name.get_string(), std::unique_ptr<Json> { new Json { std::move(json) } }));
	if (result.second == false) {
		throw ParseException { "duplicate object key "};
	}
}

}
