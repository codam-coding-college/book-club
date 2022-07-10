#pragma once

#include "json.hpp"
#include <istream>

namespace json_parse {

using Json = json::Json;
using JsonType = json::Type;
using InputStream = std::basic_istream<char>;

class ParseException: public std::exception {
	public:
		ParseException(const std::string& reason);
		virtual const char* what() const noexcept;

	private:
		std::string reason;
};

Json parse(InputStream& is);

}
