#pragma once

#include "parser.hpp"
#include <string>

namespace json_parse {

class ParserString: public Parser {
	public:
		ParseResult parse(InputStream& is);
		Json finish();

	private:
		std::string str;
};

}
