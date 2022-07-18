#include "JsonNode.h"
#include "Parser.h"

int	main(int argc, char **argv)
{
	// JsonNode* strNode = new JsonNode(std::string("HI!"));
	
	// JsonNode* arrNode = new JsonNode();
	// arrNode->setType(JsonDataType::ARRAY);
	// arrNode->addToArray(strNode);

	// JsonNode* objNode = new JsonNode();
	// objNode->setType(JsonDataType::OBJECT);
	// objNode->addToObject("array", arrNode);

	// objNode->print();
	if (argc != 2)
	{
		std::cerr << "Please enter a file!" << std::endl;
		return (1);
	}

	JsonParser	parser(argv[1]);
	JsonNode*	rootNode = parser.parse();

	rootNode->print();

	return (0);
}