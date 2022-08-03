#pragma once

#include "element_type.hpp"
#include "json_value.hpp"

#include "common/vector.hpp"
#include "common/string.hpp"
#include "embedded_list.hpp"

namespace json {

class Element;

// Internally used half-product during parsing
class ParsedJSON {
public:
	ParsedJSON() : list(this) {
		value_.pointer = 0;
		array_type = ElementType::JSON_NULL;
	}
	~ParsedJSON();
public:
	ElementType GetType() const {
		return this->type;
	}
	string GetName() const {
		return this->name;
	}
	const JSONValue& GetValue() const {
		return this->value_;
	}
	void SetName(string name);
	void SetType(ElementType type);
	void SetValueNumber(int64_t value);
	void SetValueNULL();
	void SetValueString(string value);
	void SetValueBoolean(bool value);
	void AddChild(ParsedJSON* child);
	EmbeddedList* GetList() {
		return &this->list;
	}
	Element* Finalize();
private:
	void SetPtrValue(uintptr_t ptr);
private:
	EmbeddedList list;
	ElementType type;
	string name;

	bool has_value;
	JSONValue value_;
	ElementType array_type; //! Keep track of the type of the array, to enable better type error checking
};

} //namespace json
