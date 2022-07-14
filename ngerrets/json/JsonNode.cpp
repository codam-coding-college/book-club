#include "JsonNode.h"

JsonNode::JsonNode() : m_type(JsonDataType::NULL_T) {}

JsonNode::JsonNode(int n) : m_type(JsonDataType::NUMBER)
, m_data(n) {}

JsonNode::JsonNode(bool b) : m_type(JsonDataType::BOOL)
, m_data(b) {}

JsonNode::JsonNode(const std::string& str) : m_type(JsonDataType::STRING)
, m_data(str) {}

//	DATA Struct

JsonNode::Data::Data(int n): n(n) {}
JsonNode::Data::Data(bool b): b(b) {}
JsonNode::Data::Data(const std::string& str) : str(str) {}
// JsonNode::Data::Data(std::string&& str) : str(std::move(str)) {}
// JsonNode::Data::Data(std::vector<JsonNode*>&& array)
// : array(std::move(array)) {}
// JsonNode::Data::Data(std::unordered_map<std::string, JsonNode*>&& object)
// : object(std::move(object)) {}
//JsonNode::Data::~Data() {}



//	TODO: Cleanup
JsonNode::~JsonNode() {}

void	JsonNode::addToArray(JsonNode* node)
{
	if (!m_data.array)
		m_data.array = new JsonArray();
	m_data.array->push_back(node);
}

void	JsonNode::addToObject(const std::string& key, JsonNode* value)
{
	if (!m_data.object)
		m_data.object = new JsonObject();
	//	m_data.object->insert({key, value});
	//	(*m_data.object)[key] = value;
	m_data.object->emplace(key, value);
}

void	JsonNode::_printDepth(size_t depth) const
{
	while (depth-- > 0)
		std::cout << "    ";
}

void	JsonNode::print(size_t depth) const
{
	switch (getType())
	{
		case JsonDataType::NUMBER :
			std::cout << getInt();
			break;
		case JsonDataType::BOOL :
			if (getBool())
				std::cout << "true";
			else
				std::cout << "false";
			break;
		case JsonDataType::STRING :
			std::cout << '"' << getString() << '"';
			break;
		case JsonDataType::OBJECT :
			_printObject(depth);
			break;
		case JsonDataType::ARRAY :
			_printArray(depth);
			break;
		case JsonDataType::NULL_T :
			std::cout << "null";
			break;
		default:
			std::cout << "UNKNOWN_TYPE";
	}
}

void	JsonNode::_printObject(size_t depth) const
{
	std::cout << "\n";
	_printDepth(depth);
	std::cout << '{';
	if (m_data.object->size() == 0)
	{
		std::cout << '}' << std::endl;
		return ;
	}
	std::cout << std::endl;
	for (const auto& pair : *m_data.object)
	{
		_printDepth(depth + 1);
		std::cout << '"' << pair.first << "\": ";
		pair.second->print(depth + 1);
		std::cout << std::endl;
	}
	_printDepth(depth);
	std::cout << '}' << std::endl;
}

void	JsonNode::_printArray(size_t depth) const
{
	std::cout << "[ ";
	for (size_t i = 0; i < m_data.array->size(); i++)
	{
		(*m_data.array)[i]->print(depth + 1);
		if (i < m_data.array->size() - 1)
		{
			if ((*m_data.array)[i]->getType() == JsonDataType::OBJECT)
				_printDepth(depth);
			std::cout << ", ";
		}
	}
	if ((*m_data.array)[m_data.array->size() - 1]->getType() == JsonDataType::OBJECT)
		_printDepth(depth);
	std::cout << " ]";
}
