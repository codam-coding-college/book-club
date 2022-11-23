#pragma once

namespace json {

enum class ElementType {
	UNKNOWN,
	JSON_STRING,
	JSON_NULL,
	JSON_INTEGER,
	JSON_OBJECT,
	JSON_ARRAY,
	JSON_BOOL
};

} //namespace json
