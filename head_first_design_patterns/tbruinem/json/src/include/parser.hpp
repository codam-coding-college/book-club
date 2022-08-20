#pragma once

#include <cstdint>
#include <cstddef>

#include "common/string.hpp"
#include "element_type.hpp"

namespace json {

class ParsedJSON;

enum class ParseState {
	OUT,	//! Initial state
	WORD,	//! Name of a JSON item
	VALUE,	//! Value of a JSON item
	IN,		//! Between Name and Value
};

enum class StateResult {
	CONTINUE,
	DONE,
	ERROR
};

class Parser {
public:
	Parser(string::iterator& it, const string::iterator& end, ElementType parent = ElementType::JSON_ARRAY) :
		it(it), end(end), parent(parent) {
			previous_state = ParseState::OUT;
			current_state = ParseState::OUT;
			temporary.clear();
			product = nullptr;
		}
public:
	ParsedJSON* Produce();
private:
	void	ConvertValue();
	void	UpdateState(ParseState state);

	StateResult StateOut(char c);
	StateResult StateWord(char c);
	StateResult StateValue(char c);
	StateResult StateIn(char c);

	StateResult HandleState(char c);
private:
	string::iterator& it;
	const string::iterator& end;
	ElementType	parent;

	ParseState	previous_state;
	ParseState	current_state;
	ParsedJSON	*product;
	string		temporary;
};

} //namespace json
