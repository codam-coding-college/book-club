#include "parser.hpp"
#include "parser_null.hpp"
#include "parser_array.hpp"
#include "parser_string.hpp"
#include "parser_object.hpp"
#include "parser_bool.hpp"
#include "parser_number.hpp"
#include <iostream>
#include <exception>

namespace json_parse {

void skipws(InputStream& is) {
	is >> std::ws;
}

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
			if (c == '-' || isdigit(c)) {
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
			return std::unique_ptr<Parser> { new ParserArray };
		case json::Type::Boolean:
			return std::unique_ptr<Parser> { new ParserBool };
		case json::Type::Null:
			return std::unique_ptr<Parser> { new ParserNull };
		case json::Type::Number:
			return std::unique_ptr<Parser> { new ParserNumber };
		case json::Type::Object:
			return std::unique_ptr<Parser> { new ParserObject };
		case json::Type::String:
			return std::unique_ptr<Parser> { new ParserString };
	}
	throw std::runtime_error("invalid json type");
}

static std::unique_ptr<Parser> next_state(InputStream& is) {
	skipws(is);
	json::Type state = determine_state(is.peek());
	std::cout << "State: " << state << '\n';
	return make_parser(state);
}

// This function throws an exception on error, preferably this should be a return instead since syntax errors are common
// We use a stack system to handle the recursive data structures: arrays/objects
Json ParseController::parse() {
	assert(stack.size() == 0);
	std::unique_ptr<Parser> parser = next_state(is);
	while (true) {
		skipws(is);
		Parser::ParseResult result = parser->parse(is);
		switch (result) {
			case Parser::Done:
				if (!stack.empty()) {
					Json item = parser->finish();
					parser = std::move(stack[stack.size() - 1]);
					stack.pop_back();
					parser->process_item(std::move(item));
				} else {
					return parser->finish();
				}
				break;
			case Parser::Error:
				throw ParseException { "Error Result" };
			case Parser::NextState:
				stack.push_back(std::move(parser));
				parser = next_state(is);
				break;
		}
	}

	throw std::runtime_error("invalid parse result");
}

/* Exception */

ParseException::ParseException(const std::string& reason): reason(reason) {}
const char* ParseException::what() const noexcept {
	return reason.c_str();
}

/* Main Parser Interface */

Parser::~Parser() {}

void Parser::process_item(Json&& json) {
	throw std::runtime_error("process item not implemented");
}

}
