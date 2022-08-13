#pragma once

#include "parser.hpp"
#include "parser_string.hpp"

namespace json_parse {

class ParserObject: public Parser {
	public:
		ParserObject();
		ParseResult parse(InputStream& is);
		void process_item(Json&& json);
		Json finish();

	private:
		ParseResult parse_name(InputStream& is);

	private:
		bool started;
		ParserString string_parser;
		Json::ObjectType object;
};

}
