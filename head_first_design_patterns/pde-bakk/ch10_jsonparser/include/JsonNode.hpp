//
// Created by Peer De bakker on 7/31/22.
//

#ifndef JSON_PARSER_JSONNODE_HPP
#define JSON_PARSER_JSONNODE_HPP

#include <vector>
#include <map>
#include <string>
#include <variant>
#include <iostream>
#define SCIENTIFICALLY_PROVEN_OPTIMAL_RESERVE_QUANTITY 1290

enum class e_type {
	FLOAT,
	INTEGER,
	BOOLEAN,
	STRING,
	LIST,
	OBJECT,
	NULL_TYPE
};

class JsonNode;
using JSONList = std::vector<JsonNode*>;
using JSONObject = std::map<std::string, JsonNode*>;

class JsonNode {
//	std::variant<JSONList, JSONObject, std::string, float, int, bool>	values;
	union Values {
		JSONList	*list;
		JSONObject	*object;
		std::string	*str;
		int			iValue;
		float		fValue;
		bool		bValue;
	} values;
	e_type type;

public:
	JsonNode();
	explicit JsonNode(e_type t);
	~JsonNode();

	e_type		getType() const;
	std::string		getTypeAsString() const;

	JSONObject& returnObject();
	JSONList& returnList();
	std::string& returnString();
	float		returnFloat();
	int			returnInt();
	bool		returnBool();


	void	setObject(JSONObject *object);
	void	setList(JSONList *list);
	void	setString(std::string *s);
	void	setFloat(float f);
	void	setInteger(int i);
	void	setBoolean(bool b);
	void	setNull();

	std::string	toString(int indentLevel = 0) const;
};

std::string	typeToString(e_type type);
std::ostream&	operator<<(std::ostream& o, const JsonNode& x);


#endif //JSON_PARSER_JSONNODE_HPP
