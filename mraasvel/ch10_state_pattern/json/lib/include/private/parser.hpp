#pragma once

#include "json_parse.hpp"
#include <istream>
#include <exception>
#include <memory>

namespace json_parse {

void skipws(InputStream& is);

class Parser {
	public:
		enum ParseResult {
			NextState,
			Done,
			Error,
		};

		virtual ParseResult parse(InputStream& is) = 0;
		virtual Json finish() = 0;
		virtual void process_item(Json&& json);
		virtual ~Parser();
};

class ParseController {
	public:
		ParseController(InputStream& is);
		Json parse();

	private:
		std::vector<std::unique_ptr<Parser>> stack;
		InputStream& is;
};

}
