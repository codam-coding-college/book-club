#pragma once

#include "json.hpp"
#include <istream>

namespace json_parse {

using Json = json::Json;

Json parse(std::basic_istream<char> is);

}
