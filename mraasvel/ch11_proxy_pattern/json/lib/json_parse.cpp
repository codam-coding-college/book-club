#include "json_parse.hpp"
#include "parser.hpp"

namespace json_parse {

Json parse(InputStream& is) {
	return ParseController { is }.parse();
}

}
