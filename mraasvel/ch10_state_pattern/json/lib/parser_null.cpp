#include "parser_null.hpp"

namespace json_parse {

Parser::ParseResult ParserNull::parse(InputStream& is) {
	(void)is;
	throw ParseException { "not implemented" };
}

Json ParserNull::finish() {
	throw ParseException { "not implemented" };
}

}
