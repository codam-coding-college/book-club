#include "json_parse.hpp"
#include "parser.hpp"

namespace json_parse {

Json parse(std::basic_istream<char> is) {
	return Parser { is }.parse();
}

}
