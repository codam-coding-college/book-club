#include "parser_bool.hpp"
#include <cstring>

namespace json_parse {

static Parser::ParseResult compare(void* a, void* b, size_t n) {
	if (std::memcmp(a, b, n) == 0) {
		return Parser::ParseResult::Done;
	} else {
		return Parser::ParseResult::Error;
	}
}

Parser::ParseResult ParserBool::parse(InputStream& is) {
	char buf[6];
	switch (is.peek()) {
		case 't':
			static constexpr char TRUE[] = "true";
			is.get(buf, sizeof(TRUE));
			result = true;
			return compare(buf, (void*)TRUE, sizeof(TRUE) - 1);
		case 'f':
			static constexpr char FALSE[] = "false";
			is.get(buf, sizeof(FALSE));
			result = false;
			return compare(buf, (void*)FALSE, sizeof(FALSE));
	}
	return ParseResult::Error;
}

Json ParserBool::finish() {
	return Json { result };
}

}
