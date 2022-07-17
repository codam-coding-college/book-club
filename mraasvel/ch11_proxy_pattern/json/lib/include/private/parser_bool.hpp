#pragma once

#include "parser.hpp"

namespace json_parse {

class ParserBool: public Parser {
	public:
		ParseResult parse(InputStream& is);
		Json finish();

	private:
		bool result;
};

}
