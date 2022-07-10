#include "parser.hpp"
#include "parser_null.hpp"
#include <iostream>
#include <exception>

namespace json_parse {

static JsonType determine_state(int c) {
	switch (c) {
		case '{':
			return JsonType::Object;
		case '[':
			return JsonType::Array;
		case '"':
			return JsonType::String;
		case 'f':
		case 't':
			return JsonType::Boolean;
		case 'n':
			return JsonType::Null;
		default:
			if (isdigit(c)) {
				return JsonType::Number;
			} else {
				throw ParseException{ "invalid first character" };
			}
	}
}

ParseController::ParseController(InputStream& is): is(is) {}

static std::unique_ptr<Parser> make_parser(json::Type type) {
	switch (type) {
		case json::Type::Array:
			throw ParseException { "not implemented" };
		case json::Type::Boolean:
			throw ParseException { "not implemented" };
		case json::Type::Null:
			return std::unique_ptr<Parser> { new ParserNull };
		case json::Type::Number:
			throw ParseException { "not implemented" };
		case json::Type::Object:
			throw ParseException { "not implemented" };
		case json::Type::String:
			throw ParseException { "not implemented" };
	}
	throw std::runtime_error("invalid json type");
}

int ParseController::peek() {
	return (is >> std::ws).peek();
}

Json ParseController::parse() {
	json::Type state = determine_state(peek());
	auto parser = make_parser(state);

	throw ParseException { "not implemented" };
}

/* Exception */

ParseException::ParseException(const std::string& reason): reason(reason) {}
const char* ParseException::what() const noexcept {
	return reason.c_str();
}

/* Main Parser Interface */

Parser::~Parser() {}

int Parser::get(InputStream& is) {
	return (is >> std::ws).get();
}

int Parser::peek(InputStream& is) {
	return (is >> std::ws).peek();
}

}
