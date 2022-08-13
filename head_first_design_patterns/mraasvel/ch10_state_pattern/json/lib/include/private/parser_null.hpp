#pragma once

#include "parser.hpp"

namespace json_parse {

class ParserNull: public Parser {
	public:
		ParseResult parse(InputStream& is);
		Json finish();
};

}
