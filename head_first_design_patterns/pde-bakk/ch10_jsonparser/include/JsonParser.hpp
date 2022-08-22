//
// Created by Peer De bakker on 7/31/22.
//

#ifndef JSON_PARSER_JSONPARSER_HPP
#define JSON_PARSER_JSONPARSER_HPP

#include "JsonNode.hpp"
#include <fstream>

enum class e_token
{
	CURLY_OPEN,
	CURLY_CLOSE,
	COLON,
	STRING,
	INTEGER,
	ARRAY_OPEN,
	ARRAY_CLOSE,
	COMMA,
	BOOLEAN,
	NULL_TYPE,
	END_OF_FILE
};

std::string	tokenToString(e_token token);

class JsonParser {
	std::ifstream	_file;

	JsonNode*	_root;

	JsonParser(const JsonParser& x);
	JsonParser& operator=(const JsonParser& x);
public:
	JsonParser(const std::string& filename);
	~JsonParser();

	JsonNode*	parseJSON();
private:
	JsonNode* parse(bool is_root);
//	char	get_next_char();
	e_token	parse_token();
	char get_next_nonspace();
	std::string	get_next_string();
	std::string	get_next_item();

	JsonNode*	parse_object();
	JsonNode*	parse_list();
	JsonNode*	parse_string();
	JsonNode*	parse_number();
	JsonNode*	parse_boolean();
	JsonNode*	parse_nulltype();
};

#endif //JSON_PARSER_JSONPARSER_HPP
