#include "Parser.h"

//	Returns the next key as a string
static std::string	getKey(std::fstream& stream)
{
	std::string	key = "";

	char c;
	c = nextChar(stream);
	if (c == '"')
		key = getString(stream);
	else if (c == '}' || c == ']')
		key += c;
	else
	{
		std::cerr << "BAD TOKEN: " << c << std::endl;
	}
	return (key);
}

//	This functions returns the next Json value Node
static JsonNode*	getValue(std::fstream& stream)
{
	JsonNode*	value = NULL;
	char		token;

	value = new JsonNode();
	token = nextChar(stream);
	if (token == '}' || token == ']')
	{
		stream.unget();
		return (NULL);
	}
	switch (token)
	{
		//	String
		case '"' :
			value->setType(JsonDataType::STRING);
			value->setData(getString(stream));
			break;
		case '{' :
			value->setType(JsonDataType::OBJECT);
			break;
		case '[' :
			value->setType(JsonDataType::ARRAY);
			break;
		default :
			std::string	word = token + getWord(stream);
			if (isNumber(word))
			{
				value->setType(JsonDataType::NUMBER);
				value->setData(std::stoi(word));
			}
			else if (word == "true" || word == "false")
			{
				value->setType(JsonDataType::BOOL);
				value->setData(word == "true");
			}
			else if (word != "null")
			{
				std::cerr << "UNIDENTIFIED VALUE: " << word << std::endl;
				delete value;
				return (NULL);
			}
	}
	return (value);
}

JsonParser::State	JsonParser::objectState()
{
	JsonNode*	currNode = getCurrentNode();
	JsonNode*	value;
	std::string	key;

	//	Get the key
	key = getKey(m_fileStream);
	if (key.empty())
		return (State::ERROR);
	else if (key == "}")
		return (State::OBJECT_EXIT);
	
	//	Check for the : or error
	if (char c = nextChar(m_fileStream) != ':')
	{
		std::cerr << "BAD TOKEN: " << c << std::endl;
		return (State::ERROR);
	}

	// Get the value
	value = getValue(m_fileStream);
	if (!value)
		return (State::ERROR);

	//	Now add the new key-value pair to the object
	currNode->addToObject(key, value);
	addNode(value);
	if (value->getType() == JsonDataType::ARRAY)
		return (State::ARRAY);
	return (State::OBJECT);
}

JsonParser::State	JsonParser::objectExitState()
{
	if (m_currNodeIndex == 0)
		return (State::FINISHED);
	m_currNodeIndex--;
	if (m_nodeHistory[m_currNodeIndex]->getType() == JsonDataType::OBJECT)
		return (State::OBJECT);
	return (State::ARRAY);
}

JsonParser::State	JsonParser::arrayState()
{
	JsonNode*	currNode = getCurrentNode();
	JsonNode*	value = NULL;

	value = getValue(m_fileStream);
	if (!value)
	{
		char token = nextChar(m_fileStream);
		if (token == ']')
			return (State::ARRAY_EXIT);
		else
		{
			std::cerr << "BAD TOKEN: " << token << std::endl;
			return (State::ERROR);
		}
	}
	currNode->addToArray(value);
	addNode(value);
	if (value->getType() == JsonDataType::OBJECT)
		return (State::OBJECT);
	return (State::ARRAY);
}

JsonParser::State	JsonParser::arrayExitState()
{
	m_currNodeIndex--;
	if (m_nodeHistory[m_currNodeIndex]->getType() == JsonDataType::OBJECT)
		return (OBJECT);
	return (ARRAY);
}
