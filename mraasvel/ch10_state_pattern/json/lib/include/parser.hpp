#pragma once

#include "json_parse.hpp"
#include <istream>

namespace json_parse {

/*
Example:

json_parse::Parser parser { stream };
auto json = parser.parse();
*/
class Parser {
public:
	using InputStream = std::basic_istream<char>;

public:
	Parser(InputStream& is);

	Json parse();

private:
	InputStream& is;
};

}
