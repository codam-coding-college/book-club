#ifndef PARSE_HPP
#define PARSE_HPP

#include "Json.hpp"
#include <stdlib.h>

class Parse
{
private:
	std::fstream	*_file;
	size_t			_prevPos;
	Json			*_root;
	Json			*_current;
	Json			json;

private:
	enum jsonType
	{
		CURLY_OPEN,
		CURLY_CLOSE,
		STRING,
		NUMBER,
		BOOLEAN,
		COLON,
		ARRAY_OPEN,
		ARRAY_CLOSE,
		COMMA,
		NULL_TYPE
	};

private:
	struct Type
	{
		std::string	value;
		jsonType	type;
		jsonType	nextToken;
	};

public:
	char	getWithoutWhiteSpace();
	Type	getToken();
	bool	hasMoreToken();

public:
	Parse(std::string filename);
	~Parse();

public:
	void	parse();
	Json	*parseObject(Json *node);
	void	parseArray(Json *node);
	void	parseArray1(Json *node);
	void	parseTest(Json *node);
	void	rollBackToken();
	Json	parseString();
	Json	parseNumber();
	Json	parseList();
	Json	parseBoolean();
	Json	parseNull();
};

#endif