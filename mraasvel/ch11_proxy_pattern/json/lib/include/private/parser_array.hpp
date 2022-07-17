#pragma once

#include "parser.hpp"

namespace json_parse {

class ParserArray: public Parser {
	public:
		ParseResult parse(InputStream& is);
		void process_item(Json&& json);
		Json finish();

	private:
		Json::ArrayType array;
};

}
