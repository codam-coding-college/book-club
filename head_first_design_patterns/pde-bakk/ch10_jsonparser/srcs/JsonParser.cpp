//
// Created by Peer De bakker on 7/31/22.
//

#include "JsonParser.hpp"

#include <iostream>
#include <cctype>
#include <algorithm>

e_type	token_to_type(e_token token) {
	switch (token) {
		case (e_token::CURLY_OPEN):
			return (e_type::OBJECT);
		case (e_token::STRING):
			return (e_type::STRING);
		case (e_token::INTEGER):
			return (e_type::INTEGER);
		case (e_token::ARRAY_OPEN):
			return (e_type::LIST);
		case (e_token::BOOLEAN):
			return (e_type::BOOLEAN);
		case (e_token::NULL_TYPE):
			return (e_type::NULL_TYPE);
		default:
			throw std::runtime_error("WHAT TYPE IS THIS? " + tokenToString(token));
	}
}

JsonParser::JsonParser(const std::string& filename) : _file(filename), _root(nullptr) {
	if (!_file) {
		throw std::runtime_error("unable to open file '" + filename + "'");
	}
}

JsonParser::~JsonParser() {

}
JsonNode* JsonParser::parseJSON() {
	return (this->parse(true));
}

JsonNode* JsonParser::parse(const bool is_root = false) {
	if (_file.eof()) {
		return (nullptr);
	}
	e_token token = this->parse_token();
	if (token == e_token::END_OF_FILE) {
		return (nullptr);
	}
	e_type type = token_to_type(token);
	JsonNode*	node = nullptr;
	switch (type) {
		case (e_type::FLOAT):
		case (e_type::INTEGER):
			node = parse_number();
			break ;
		case (e_type::BOOLEAN):
			node = parse_boolean();
			break ;
		case (e_type::STRING):
			node = parse_string();
			break ;
		case (e_type::LIST):
			node = parse_list();
			break ;
		case (e_type::OBJECT):
			node = parse_object();
			break ;
		case (e_type::NULL_TYPE):
			node = parse_nulltype();
			break ;
	}
	if (is_root) {
		if (_file.eof() || this->get_next_nonspace() <= 0) {
			this->_root = node;
		} else {
			delete node;
			throw std::runtime_error("Error: found extraneous characters");
		}
	}
	return (node);
}

static e_token parse_int(char c) {
	//TODO: check if float
	if ((c >= '0' && c <= '9') || c == '+' || c == '-')
		return (e_token::INTEGER);
	std::string error("Number: Invalid token: ");
	error.push_back(c);
	throw std::runtime_error(error);
}

e_token JsonParser::parse_token() {
	char c = get_next_nonspace();

	switch (c) {
		case '\0':
			return (e_token::END_OF_FILE);
		case '{':
			return (e_token::CURLY_OPEN);
		case '}':
			return (e_token::CURLY_CLOSE);
		case ':':
			return (e_token::COLON);
		case '"':
			return (e_token::STRING);
		case '[':
			return (e_token::ARRAY_OPEN);
		case ']':
			return (e_token::ARRAY_CLOSE);
		case ',':
			return (e_token::COMMA);
		case 't':
		case 'f':
			this->_file.unget();
			return (e_token::BOOLEAN);
		case 'n':
			this->_file.unget();
			return (e_token::NULL_TYPE);
		default:
			this->_file.unget();
			return (parse_int(c));
	}
}

JsonNode* JsonParser::parse_object() {
	JsonNode*	node = new JsonNode();
	JSONObject*	object = new JSONObject();
	node->setObject(object);

	if (!_file.eof() && _file.peek() == '}') {
		_file.get();
		return (node);
	}
	while (!_file.eof()) {
		char c = this->get_next_nonspace();

		if (c != '"') {
			throw std::runtime_error("Object key needs to be within double-quotes (\"key\")");
		}
		std::string key = get_next_string();
		char colon = this->get_next_nonspace();
		if (colon != ':')
			throw std::runtime_error("Object key needs to be followed by a colon (:)");
		JsonNode*	value = parse();
		if (value == nullptr)
			throw std::runtime_error("Error trying to parse object value");
		(*object)[key] = value;
		c = this->get_next_nonspace();
		if (c == '}') {
			break ;
		} else if (c != ',') {
			throw std::runtime_error("Object kv-pair wasn't followed by comma or closing bracket");
		}
	}
	return (node);
}

JsonNode* JsonParser::parse_list() {
	JsonNode*	node = new JsonNode();
	JSONList*	list = new JSONList();

	node->setList(list);
	if (!_file.eof() && _file.peek() == ']') {
		_file.get();
		return (node);
	}
	while (!_file.eof()) {
		char c = this->get_next_nonspace();
		this->_file.unget();
		JsonNode*	new_elem = this->parse();
		if (new_elem == nullptr) {
			throw std::runtime_error("Error trying to parse list value");
		}
		list->push_back(new_elem);

		c = this->get_next_nonspace();
		if (c == ']') {
			break ;
		}
		else if (c != ',') {
			throw std::runtime_error("List item wasn't followed by comma or closing bracket");
		}
	}

	return (node);
}

JsonNode* JsonParser::parse_string() {
	const auto next = get_next_string();
	std::string* s = new std::string(next);
	JsonNode* node = new JsonNode();
	node->setString(s);
	return (node);
}

JsonNode* JsonParser::parse_number() {
	const auto next = get_next_item();
	JsonNode* node = nullptr;
	std::string::size_type pos;
	const size_t amount_dots = std::count(next.begin(), next.end(), '.');

	if (amount_dots > 1 || (amount_dots == 1 && next.back() == '.')) {
		throw std::runtime_error("Invalid float: " + next);
	}
	if (amount_dots == 0) {
		// int
		int val = std::stoi(next, &pos);
		if (pos != next.size()) {
			throw std::runtime_error("Invalid integer: " + next);
		}
		node = new JsonNode();
		node->setInteger(val);
	} else {
		float val = std::stof(next, &pos);
		if (pos != next.size()) {
			throw std::runtime_error("Invalid float: " + next);
		}
		node = new JsonNode();
		node->setFloat(val);
	}
	return (node);
}

JsonNode* JsonParser::parse_boolean() {
	const auto next = get_next_item();
	bool value;
	if (next == "true")
		value = true;
	else if (next == "false")
		value = false;
	else
		throw std::runtime_error("Invalid boolean: " + next);
	JsonNode* node = new JsonNode();
	node->setBoolean(value);
	return (node);
}

JsonNode* JsonParser::parse_nulltype() {
	const auto next = get_next_item();
	if (next != "null")
		throw std::runtime_error("Invalid nulltype: " + next);
	JsonNode* node = new JsonNode();
	node->setNull();
	return (node);
}

std::string JsonParser::get_next_item() {
	std::string str;

	str.reserve(SCIENTIFICALLY_PROVEN_OPTIMAL_RESERVE_QUANTITY);

	skipws(this->_file);
	while (!_file.eof()) {
		char newchar = _file.get();
		if (_file.eof())
			break;
		if (isspace(newchar) || newchar == ',' || newchar == '}' || newchar == ']') {
			this->_file.unget();
			break ;
		} else if (newchar == '\0')
			break ;
		str += newchar;
	}
	return (str);
}

static char	unescape_character(const char c) {
	switch (c) {
		case ('b'):
			return ('\b');
		case ('f'):
			return ('\f');
		case ('n'):
			return ('\n');
		case ('t'):
			return ('\t');
		case ('r'):
			return ('\r');
		case ('\\'):
			return ('\\');
		case ('"'):
			return ('\"');
		default:
			throw std::runtime_error(std::string("bad esacape sequence \\") + c);
	}
}

std::string JsonParser::get_next_string() {
	std::string str;

	str.reserve(SCIENTIFICALLY_PROVEN_OPTIMAL_RESERVE_QUANTITY);

	skipws(this->_file); // TODO: if theres spaces inside quotations, change
	while (!_file.eof()) {
		const char newchar = _file.get();
		if (_file.eof())
			break ;
		if (newchar == '\\') {
			const char escape = _file.get();
			if (_file.eof()) {
				throw std::runtime_error("Invalid string: Not allowed to end with a single backslash");
			}
			str += unescape_character(escape);
			continue ;
		}
		if (newchar == '"') {
			break ;
		}
		str += newchar;
	}
	return (str);
}

char JsonParser::get_next_nonspace() {
	char c = _file.get();
	while (isspace(c) && !this->_file.eof()) {
		c = _file.get();
	}
	return (c);
}

std::string	tokenToString(const e_token token) {
	switch (token) {
		case e_token::CURLY_OPEN:
			return ("e_token::CURLY_OPEN");
		case e_token::CURLY_CLOSE:
			return ("e_token::CURLY_CLOSE");
		case e_token::COLON:
			return ("e_token::COLON");
		case e_token::STRING:
			return ("e_token::STRING");
		case e_token::INTEGER:
			return ("e_token::INTEGER");
		case e_token::ARRAY_OPEN:
			return ("e_token::ARRAY_OPEN");
		case e_token::ARRAY_CLOSE:
			return ("e_token::ARRAY_CLOSE");
		case e_token::COMMA:
			return ("e_token::COMMA");
		case e_token::BOOLEAN:
			return ("e_token::BOOLEAN");
		case e_token::NULL_TYPE:
			return ("e_token::NULL_TYPE");
		default:
			return ("e_token::BAD");
	}
}
