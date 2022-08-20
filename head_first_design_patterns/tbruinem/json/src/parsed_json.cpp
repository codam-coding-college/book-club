#include "parsed_json.hpp"
#include "element.hpp"

#include <assert.h>

namespace json {

ParsedJSON::~ParsedJSON() {
}

void ParsedJSON::SetName(string name)
{
	this->name = name;
}

void ParsedJSON::SetPtrValue(uintptr_t ptr) {
	assert(this->value_.pointer == 0);
	this->value_.pointer = ptr;
}

void ParsedJSON::SetType(ElementType type)
{
	this->type = type;
}

void ParsedJSON::SetValueNumber(int64_t value)
{
	this->value_.bigint = value;
}

void ParsedJSON::SetValueNULL()
{
	this->value_.pointer = 0;
}

void ParsedJSON::SetValueString(string value)
{
	SetPtrValue((uintptr_t)new string(value));
}

void ParsedJSON::SetValueBoolean(bool value)
{
	this->value_.boolean = value;
}

ElementType UpgradeType(ElementType current, ElementType new_element) {
	if (current == ElementType::JSON_NULL) {
		return new_element;
	}
	if (new_element == ElementType::JSON_NULL) {
		return current;
	}
	if (current != new_element) {
		throw std::runtime_error("JSON types are not compatible!");
	}
	return current;
}

void ParsedJSON::AddChild(ParsedJSON* child)
{
	if (!value_.pointer) {
		value_.pointer = (uintptr_t)child;
	}
	else {
		auto chain = (ParsedJSON*)value_.pointer;
		chain->list.AddBack(&child->list);
	}

	// // Check array constraints
	// if (type == ElementType::JSON_ARRAY) {
	// 	array_type = UpgradeType(array_type, child->type);
	// }
}

static element_create_fun_t GetFinalizeFunction(ElementType type) {
	switch (type) {
	case ElementType::JSON_BOOL: return Element::BOOL;
	case ElementType::JSON_INTEGER: return Element::NUMBER;
	case ElementType::JSON_NULL: return Element::NULL_ELEM;
	case ElementType::JSON_STRING: return Element::STRING;
	case ElementType::JSON_OBJECT: return Element::GROUP;
	case ElementType::JSON_ARRAY: return Element::ARRAY;
	default:
		throw std::runtime_error("GetFinalizeFunction - type not implemented");
	}
}

//! Returns ownership of this memory
Element* ParsedJSON::Finalize()
{
	element_create_fun_t create = GetFinalizeFunction(this->type);
	return new Element(move(create(move(*this))));
}

} //namespace json
