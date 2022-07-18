#include "Parser.h"

bool	isNumber(const std::string &str)
{
	for (const char& c : str)
	{
		if (!isdigit(c))
			return (false);
	}
	return (true);
}

char	isToken(char c)
{
	static const std::string tokens("{}[]\":");

	if (tokens.find(c) == std::string::npos)
		return (0);
	return (c);
}

std::string	getWord(std::fstream& stream)
{
	std::string	str = "";

	char c;
	while (stream.get(c))
	{
		if (!isalnum(c))
			return (str);
		str += c;
	}
	return (str);
}

std::string	getString(std::fstream& stream)
{
	std::string	str = "";

	char c;
	while (stream.get(c))
	{
		if (c == '"' || c == '\n' || c == '\0')
			return (str);
		str += c;
	}
	return (str);
}

//	Ingores commas for now :D
char	nextChar(std::fstream& stream)
{
	char c;
	while (stream.get(c))
	{
		if (stream.eof() || c == '\0')
			return ('\0');
		if (!isspace(c) && c != ',')
			return (c);
	}
	return ('\0');
}