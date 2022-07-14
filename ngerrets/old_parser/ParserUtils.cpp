#include "Parser.h"

bool	isNumber(const std::string &s)
{
	return (!s.empty() && std::all_of(s.begin(), s.end(), ::isdigit));
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