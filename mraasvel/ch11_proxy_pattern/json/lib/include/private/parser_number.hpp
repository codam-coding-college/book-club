#pragma once

#include "parser.hpp"

namespace json_parse {

class ParserNumber: public Parser {
	public:
		ParseResult parse(InputStream& is);
		Json finish();

	private:
		double d;
};

}
