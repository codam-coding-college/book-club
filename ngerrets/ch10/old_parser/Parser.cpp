#include "Parser.h"

JsonParser::JsonParser(const char *fname)
{
	//	Open the filestream
	m_fileStream.open(fname);
	if (m_fileStream.bad())
	{
		std::cerr << "Can't open file: " << fname << std::endl;
		return ;
	}

	//	Set the first node (rootNode)
	m_nodeHistory[0] = new JsonNode();
	m_nodeHistory[0]->setType(JsonDataType::OBJECT);
	m_currNodeIndex = 0;
}

JsonParser::~JsonParser()
{
	m_fileStream.close();
}

JsonNode*	JsonParser::getRootNode() const
{
	return (m_nodeHistory[0]);
}

JsonNode*	JsonParser::parse()
{
	//	First state is the object state
	State	currState = State::OBJECT;

	char c;
	m_fileStream.get(c);
	if (c != '{')
		m_fileStream.unget();
	//	Continue until we are in the FINISHED state
	while (currState != State::FINISHED)
	{
		if (m_fileStream.eof())
			return (getRootNode());
		switch (currState)
		{
			case State::OBJECT :
				currState = objectState();
				break;
			case State::OBJECT_EXIT :
				currState = objectExitState();
				break;
			case State::ARRAY :
				currState = arrayState();
				break;
			case State::ARRAY_EXIT :
				currState = arrayExitState();
				break;
			case State::ERROR :
				std::cerr << "Error occured while parsing json file." << std::endl;
				return (NULL);
			default:
				return (getRootNode());
		}
	}
	return (getRootNode());
}

JsonNode*	JsonParser::getCurrentNode()
{
	return (m_nodeHistory[m_currNodeIndex]);
}

void	JsonParser::addNode(JsonNode* node)
{
	if (node && (node->getType() == JsonDataType::ARRAY || node->getType() == JsonDataType::OBJECT))
	{
		m_currNodeIndex++;
		m_nodeHistory[m_currNodeIndex] = node;
	}
}
