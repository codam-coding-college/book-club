#include "element.hpp"
#include <assert.h>

#include "common/iostream.hpp"

namespace json {

Element::~Element()
{
	children.clear();
}

const ElementType& Element::Type() const
{
	return this->type;
}

void	Element::SetBasicValues(ParsedJSON& json) {
	this->type = json.GetType();
	this->name = json.GetName();
	this->value_ = json.GetValue();
	json.SetValueNULL();
}

Element Element::STRING(ParsedJSON json)
{
	auto element = Element();
	element.SetBasicValues(json);
	assert(element.type == ElementType::JSON_STRING);
	return move(element);
}

Element Element::BOOL(ParsedJSON json)
{
	auto element = Element();
	element.SetBasicValues(json);
	assert(element.type == ElementType::JSON_BOOL);
	return move(element);
}

static void FillChildrenVector(vector<unique_ptr<Element>>& children, ParsedJSON* elements) {
	EmbeddedList* list = elements->GetList();
	while (list) {
		auto* parsed = (ParsedJSON*)list->holder;
		children.push_back(move(unique_ptr<Element>(parsed->Finalize())));
		list = list->Next();
		delete(parsed);
	}
}

Element Element::ARRAY(ParsedJSON json)
{
	auto element = Element();
	element.SetBasicValues(json);
	assert(element.type == ElementType::JSON_ARRAY);
	FillChildrenVector(element.children, (ParsedJSON*)element.value_.pointer);
	return move(element);
}

Element Element::GROUP(ParsedJSON json)
{
	auto element = Element();
	element.SetBasicValues(json);
	assert(element.type == ElementType::JSON_OBJECT);
	FillChildrenVector(element.children, (ParsedJSON*)element.value_.pointer);
	return move(element);
}

Element Element::NULL_ELEM(ParsedJSON json)
{
	auto element = Element();
	element.SetBasicValues(json);
	assert(element.type == ElementType::JSON_NULL);
	return move(element);
}

Element Element::NUMBER(ParsedJSON json)
{
	auto element = Element();
	element.SetBasicValues(json);
	assert(element.type == ElementType::JSON_INTEGER);
	return move(element);
}

static string Indent(size_t depth) {
	return string(depth, '\t');
}

static string Name(const string& name) {
	if (name.empty()) {
		return "";
	}
	else {
		return "\"" + name + "\": ";
	}
}

static string Value(vector<unique_ptr<Element>>& children, const JSONValue& val, ElementType& type, size_t indent_level) {
	switch (type) {
		case ElementType::JSON_BOOL: {
			return val.boolean ? "true" : "false";
		}
		case ElementType::JSON_INTEGER: {
			return std::to_string(val.bigint);
		}
		case ElementType::JSON_STRING: {
			return "\"" + *((string*)(val.pointer)) + "\"";
		}
		case ElementType::JSON_NULL: {
			return "null";
		}
		case ElementType::JSON_OBJECT:
		case ElementType::JSON_ARRAY: {
			char brackets[2][2] = {
				{
					'[',
					']'
				},
				{
					'{',
					'}'
				}
			};
			size_t bracket_idx = type == ElementType::JSON_OBJECT;
			string result;
			result += string(1, brackets[bracket_idx][0]) + "\n";
			for (size_t i = 0; i < children.size(); i++) {
				result += children[i]->ToString(indent_level + 1);
				if (i + 1 < children.size()) {
					auto child_type = children[i]->Type();
					if (child_type == ElementType::JSON_ARRAY || child_type == ElementType::JSON_OBJECT) {
						result += Indent(indent_level + 1);
					}
					result += ",";
				}
				result += "\n";
			}
			result += Indent(indent_level) + string(1, brackets[bracket_idx][1]) + "\n";
			return result;
		}
		default: {
			throw std::runtime_error("'Value' - no behavior defined for type of ElementType");
		}
	}
	return "";
}

string Element::ToString(size_t indent_level)
{
	return Indent(indent_level) + Name(name) + Value(children, value_, type, indent_level);
}

} //namespace json
