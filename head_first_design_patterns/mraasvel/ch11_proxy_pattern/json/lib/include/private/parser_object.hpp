#pragma once

#include "parser.hpp"
#include "parser_string.hpp"

namespace json_parse {

class ParserObject: public Parser {
	public:
		ParseResult parse(InputStream& is);
		void process_item(Json&& json);
		Json finish();

	private:
		ParseResult parse_name(InputStream& is);

	private:
		ParserString string_parser;
		Json::ObjectType object;
};

}
