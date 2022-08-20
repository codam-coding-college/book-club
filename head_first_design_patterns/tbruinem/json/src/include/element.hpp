#pragma once

#include "json_value.hpp"
#include "element_type.hpp"
#include "parsed_json.hpp"
#include "common/memory.hpp"

#include "common/vector.hpp"

namespace json {

class Element {
public:
	const ElementType& Type() const;
	static Element STRING(ParsedJSON json);
	static Element BOOL(ParsedJSON json);
	static Element ARRAY(ParsedJSON json);
	static Element GROUP(ParsedJSON json);
	static Element NULL_ELEM(ParsedJSON json);
	static Element NUMBER(ParsedJSON json);
	string ToString(size_t indent_level);
protected:
	Element() {
		name.clear();
	}
protected:
	ElementType type;
	string name;
	JSONValue value_;
	vector<unique_ptr<Element>> children;
private:
	void SetBasicValues(const ParsedJSON& json);
};

typedef Element (*element_create_fun_t)(ParsedJSON);

} //namespace json
