#pragma once

#include <cstdint>

namespace json {

union JSONValue {
	int8_t boolean;
	int64_t bigint;
	uintptr_t pointer;
};

} //namespace json
