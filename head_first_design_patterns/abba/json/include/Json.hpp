#ifndef JSON_HPP
#define JSON_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Json;

using jsonObject = std::map<std::string, Json*>;
using jsonList = std::vector<Json*>;

class Json
{
private:
	std::fstream	_file;

public:
	enum Type
	{
		STRING,
		NUMBER,
		BOOLEAN,
		ARRAY,
		OBJECT,
		NULL_TYPE
	};
public:
	Type type;
	struct values
	{
		values() {}
		jsonList	list;
		jsonObject	object;
		std::string str;
		int			number;
		bool		boolean;
		~values() {}
	}		values;
	std::fstream	&getFile();

public:
	Json(std::string file_name);
	Json() {}
	~Json();
};

#endif
