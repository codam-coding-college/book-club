#pragma once

#include "parser.hpp"

namespace json_parse {

class ParserArray: public Parser {
	public:
		ParserArray();
		ParseResult parse(InputStream& is);
		void process_item(Json&& json);
		Json finish();

	private:
		bool started;
		Json::ArrayType array;
};

}
