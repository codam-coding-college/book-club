#include "parser_array.hpp"
#include <cstring>
#include <iostream>

namespace json_parse {

ParserArray::ParserArray(): started(false) {}

Parser::ParseResult ParserArray::parse(InputStream& is) {
	if (!started) {
		assert(is.get() == '[');
		skipws(is);
	}
	switch (is.peek()) {
		case ']':
			is.ignore();
			return ParseResult::Done;
		case ',':
			is.ignore();
			return ParseResult::NextState;
		default:
			if (!started) {
				started = true;
				return ParseResult::NextState;
			}
			return ParseResult::Error;
	}
}

Json ParserArray::finish() {
	return Json { std::move(array) };
}

void ParserArray::process_item(Json&& json) {
	array.emplace_back(std::unique_ptr<Json> { new Json { std::move(json) } });
}

}
