#pragma once

#include "json_parse.hpp"
#include <istream>
#include <exception>
#include <memory>

namespace json_parse {

class Parser {
	public:
		enum ParseResult {
			Continue,
			NextState,
			Done,
			Error,
		};

		virtual ParseResult parse(InputStream& is) = 0;
		virtual Json finish() = 0;
		int get(InputStream& is);
		int peek(InputStream& is);
		virtual ~Parser();
};

class ParseController {
	public:
		ParseController(InputStream& is);
		Json parse();

	private:
		int peek();

	private:
		std::vector<std::unique_ptr<Parser>> stack;
		InputStream& is;
};

}
