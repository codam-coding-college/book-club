#include "Parse.hpp"

Parse::Parse(std::string filename) : json(filename)
{

}

void Parse::parse()
{
	_file = &json.getFile();
	std::cout << "i'm here" << std::endl;
	getToken();
	Json *root = new Json();
	root->type = Json::OBJECT;
	root = parseObject(root);
	std::cout << "DONE PARSING!!!!!!!!!!!!" << std::endl;
}

char Parse::getWithoutWhiteSpace()
{
	std::cout << "getWithoutWhiteSpace function called" << std::endl;
	char	c = ' ';
	while (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r')
	{
		_file->get(c);
		if (!_file)
			return c;
	}
	return c;
}

Parse::Type Parse::getToken()
{
	char		c;
	Type	type;

//	std::cout << "getToken function called" << std::endl;
	if (_file->eof())
	{
		std::cout << "finish reading" << std::endl;
	}
	_prevPos = _file->tellg();
	c = getWithoutWhiteSpace();
	if (c == '"')
	{
		type.type = STRING;
		_file->get(c);
		while (c != '\n' && c != '"')
		{
			type.value += c;
			_file->get(c);
		}
	}
	else if (c == '[')
	{
//		std::cout << "array open" << std::endl;
		type.type = ARRAY_OPEN;
	}
	else if (c == ']')
	{
//		std::cout << "array close" << std::endl;
		type.type = ARRAY_CLOSE;
	}
	else if (c == '{')
	{
//		std::cout << "curly open" << std::endl;
		type.type = CURLY_OPEN;
	}
	else if (c == '}')
		type.type = CURLY_CLOSE;
	else if (c == ':')
		type.type = COLON;
	else if (c == ',')
		type.type = COMMA;
	else if (c >= '0' && c <= '9')
	{
		type.type = NUMBER;
		while (c >= '0' && c <= '9')
		{
			_prevPos = _file->tellg();
			type.value += c;
			_file->get(c);
		}
		_file->seekg(_prevPos);
	}
	else if (c == 'n')
	{
		type.type = NULL_TYPE;
		while (isalpha(c))
		{
			_prevPos = _file->tellg();
			type.value += c;
			_file->get(c);
		}
		_file->seekg(_prevPos);
	}
	else if (c == 't' || c == 'f')
	{
		type.type = BOOLEAN;
		while (isalpha(c))
		{
			_prevPos = _file->tellg();
			type.value += c;
			_file->get(c);
		}
		_file->seekg(_prevPos);
	}
	return type;
}

bool Parse::hasMoreToken()
{
	return !_file->eof();
}

Parse::~Parse()
{

}

Json *Parse::parseObject(Json *node)
{
//	std::cout << "parsing object" << std::endl;
	bool		endObj;

	endObj = false;
	while (!endObj)
	{
		if (hasMoreToken())
		{
			Type type;
			type = getToken();
			std::string value = type.value;
			if (getToken().type != COLON)
			{
				std::cout << "bus error" << std::endl;
				exit(0);
			}
			type = getToken();
			switch (type.type)
			{
				case CURLY_OPEN:
				{
					node->type = Json::OBJECT;
					parseTest(node);
					_file->seekg(_prevPos);
					break;
				}
				case CURLY_CLOSE:
				{
					endObj = true;
					break;
				}
				case STRING:
				{
					node->type = Json::STRING;
					node->values.str = type.value;
					node->values.object.emplace(value, node);
					break;
				}
				case NUMBER:
				{
					node->type = Json::NUMBER;
					node->values.number = std::stoi(type.value);
					node->values.object.emplace(value, node);
					break;
				}
				case BOOLEAN:
				{
					node->type = Json::BOOLEAN;
					(type.value == "true") ? node->values.boolean = true : node->values.boolean = false;
					node->values.object.emplace(value, node);
					break;
				}
				case COLON:
					break;
				case ARRAY_OPEN:
				{
//					std::cout << "parsing array" << std::endl;
					node->type = Json::ARRAY;
					type = getToken();
					if (type.type == CURLY_OPEN)
					{
						parseTest(node);
//						node->values.object.emplace(value, node);
//						while (type.type != ARRAY_CLOSE)
//						{
//							parseArray(node);
//							_file->seekg(_prevPos);
//							type = getToken();
//							if (type.type == COMMA)
//								type = getToken();
//						}
					}
					else
					{
						_file->seekg(_prevPos);
						node->values.str = value;
						node->values.list.push_back(node);
						parseArray1(node);
					}
					break;
				}
				case ARRAY_CLOSE:
				{
					endObj = true;
					break;
				}
				case COMMA:
					break;
				case NULL_TYPE:
				{
					node->type = Json::NULL_TYPE;
					node->values.str = type.value;
					node->values.object.emplace(value, node);
					break;
				}
			}
			if (getToken().type == CURLY_CLOSE)
			{
//				endObj = true;
			}
		}
	}
	return node;
}

void Parse::parseTest(Json *node)
{
	bool	finish = false;
	while (!finish)
	{
		Type type = getToken();
		std::string value = type.value;
		if (getToken().type != COLON)
		{
			std::cout << "bus error" << std::endl;
			exit(0);
		}
		type = getToken();
		switch (type.type)
		{
			case CURLY_OPEN:
				break;
			case CURLY_CLOSE:
				break;
			case STRING:
			{
				node->type = Json::STRING;
				node->values.str = type.value;
				std::cout << type.value << std::endl;
				node->values.object.emplace(value, node);
				break;
			}
			case NUMBER:
			{
				node->type = Json::NUMBER;
				node->values.number = std::stoi(type.value);
				node->values.object.emplace(value, node);
				break;
			}
			case BOOLEAN:
			{
				node->type = Json::BOOLEAN;
				(type.value == "true") ? node->values.boolean = true : node->values.boolean = false;
				node->values.object.emplace(value, node);
				break;
			}
			case COLON:
				break;
			case ARRAY_OPEN:
			{
				node->type = Json::ARRAY;
//				type = getToken();
				if (type.type == CURLY_OPEN)
				{
					node->values.object.emplace(value, node);
					while (type.type != ARRAY_CLOSE)
					{
						parseArray(node);
						_file->seekg(_prevPos);
						type = getToken();
						if (type.type == COMMA)
							type = getToken();
					}
				}
				else
				{
//					_file->seekg(_prevPos);
					_prevPos = _file->tellg();
					node->values.str = value;
					node->values.list.push_back(node);
					parseArray1(node);
					_file->seekg(_prevPos);
					finish = true;
				}
				break;
			}
			case ARRAY_CLOSE:
				break;
			case COMMA:
				break;
			case NULL_TYPE:
			{
				node->type = Json::NULL_TYPE;
				node->values.str = type.value;
				node->values.object.emplace(value, node);
				break;
			}
		}
		if (getToken().type == CURLY_CLOSE)
		{
			finish = true;
			_prevPos = _file->tellg();
		}
	}
}

void Parse::parseArray(Json *node)
{
	bool	finish = false;
	while (!finish)
	{
		Type type;
		type = getToken();
		std::string value = type.value;
		if (getToken().type != COLON)
		{
			std::cout << "bus error" << std::endl;
			exit(0);
		}
		type = getToken();
		switch (type.type)
		{
			case CURLY_OPEN:
				break;
			case CURLY_CLOSE:
				break;
			case STRING:
			{
				node->type = Json::STRING;
				node->values.str = type.value;
				std::cout << type.value << std::endl;
				node->values.object.emplace(value, node);
				break;
			}
			case NUMBER:
			{
				node->type = Json::NUMBER;
				node->values.number = std::stoi(type.value);
				node->values.object.emplace(value, node);
				break;
			}
			case BOOLEAN:
			{
				node->type = Json::BOOLEAN;
				(type.value == "true") ? node->values.boolean = true : node->values.boolean = false;
				node->values.object.emplace(value, node);
				break;
			}
			case COLON:
				break;
			case ARRAY_OPEN:
			{
				node->type = Json::ARRAY;
//				type = getToken();
				if (type.type == CURLY_OPEN)
				{
					node->values.object.emplace(value, node);
					while (type.type != ARRAY_CLOSE)
					{
						parseArray(node);
						_file->seekg(_prevPos);
						type = getToken();
						if (type.type == COMMA)
							type = getToken();
					}
				}
				else
				{
//					_file->seekg(_prevPos);
					_prevPos = _file->tellg();
					node->values.str = value;
					node->values.list.push_back(node);
					parseArray1(node);
					_file->seekg(_prevPos);
					finish = true;
				}
				break;
			}
			case ARRAY_CLOSE:
				break;
			case COMMA:
				break;
			case NULL_TYPE:
			{
				node->type = Json::NULL_TYPE;
				node->values.str = type.value;
				node->values.object.emplace(value, node);
				break;
			}
		}
		if (getToken().type == CURLY_CLOSE)
		{
			finish = true;
			_prevPos = _file->tellg();
		}
	}
}

void Parse::parseArray1(Json *node)
{
	bool	finish = false;
	while (!finish)
	{
		Type type;
		type = getToken();
		std::string value = type.value;
		switch (type.type)
		{
			case CURLY_OPEN:
				break;
			case CURLY_CLOSE:
				break;
			case STRING:
			{
				node->type = Json::STRING;
				node->values.str = type.value;
				std::cout << type.value << std::endl;
				node->values.list.push_back(node);
				break;
			}
			case NUMBER:
			{
				node->type = Json::NUMBER;
				node->values.number = std::stoi(type.value);
				node->values.list.push_back(node);
				break;
			}
			case BOOLEAN:
			{
				node->type = Json::BOOLEAN;
				(type.value == "true") ? node->values.boolean = true : node->values.boolean = false;
				node->values.list.push_back(node);
				break;
			}
			case COLON:
				break;
			case ARRAY_OPEN:
				break;
			case ARRAY_CLOSE:
				break;
			case COMMA:
				break;
			case NULL_TYPE:
			{
				node->type = Json::NULL_TYPE;
				node->values.str = type.value;
				node->values.list.push_back(node);
				break;
			}
		}
		if (getToken().type == ARRAY_CLOSE)
		{
			finish = true;
//			_prevPos = _file->tellg();
		}
	}
}

void	Parse::rollBackToken()
{
	if (_file->eof())
	{
		_file->clear();
	}
	_file->seekg(_prevPos);
}

