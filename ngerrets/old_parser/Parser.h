#include "JsonNode.h"
#include <fstream>

#define MAX_HISTORY 256

class JsonParser
{

	public:
		enum State
		{
			OBJECT,
			OBJECT_EXIT,
			ARRAY,
			ARRAY_EXIT,
			ERROR,
			FINISHED
		};

	typedef State (*JsonStateFunction)();

	public:
		JsonParser(const char *fname);
		~JsonParser();

		JsonNode*	parse();
		JsonNode*	getRootNode() const;

	private:
		State			m_parseState;
		std::fstream	m_fileStream;

		JsonNode*		m_nodeHistory[MAX_HISTORY];
		size_t			m_currNodeIndex;

		static JsonStateFunction	_getStateFunction(State state);
	
	private:
		JsonNode*		getCurrentNode();
		void			addNode(JsonNode* node);

		//	parser state functions
		State			objectState();
		State			objectExitState();
		State			arrayState();
		State			arrayExitState();

};

/* ParserUtils */
bool		isNumber(const std::string &str);
char		isToken(char c);
std::string	getWord(std::fstream& stream);
std::string	getString(std::fstream& stream);
char		nextChar(std::fstream& stream);
