#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

enum class JsonDataType
{
	OBJECT,
	STRING,
	NUMBER,
	ARRAY,
	BOOL,
	NULL_T
};

class JsonNode
{
	public:
		//	An object is a map of key:value pairs
		using JsonObject = std::unordered_map<std::string, JsonNode*>;
		//	An Array is just a list/vector of JsonNodes
		using JsonArray = std::vector<JsonNode*>;

	public:
		JsonNode();
		JsonNode(int n);
		JsonNode(const std::string& str);
		JsonNode(bool b);
		~JsonNode();

		inline JsonDataType	getType() const { return m_type; }
		inline void			setType(JsonDataType type) { m_type = type; }

		inline void	setData(const std::string& str) { m_data.str = str; }
		inline void	setData(int n) { m_data.n = n; }
		inline void	setData(bool b) { m_data.b = b; }

		//	Get data
		inline int					getInt() const { return m_data.n; }
		inline bool					getBool() const { return m_data.b; }
		inline const std::string&	getString() const { return m_data.str; }
		inline const JsonObject*	getMap() const { return m_data.object; }
		inline const JsonArray*		getVector() const { return m_data.array; }

		void	print(size_t depth = 0) const;
		void	addToObject(const std::string& key, JsonNode* value);
		void	addToArray(JsonNode* node);

	private:
		void	_printDepth(size_t depth) const;
		void	_printObject(size_t depth = 0) const;
		void	_printArray(size_t depth = 0) const;

		JsonDataType	m_type;

		union	Data
		{
			Data() {}
			Data(int n);
			Data(bool b);
			Data(const std::string& str);
			~Data() {};

			//	Using pointers because vectors/maps in unions screw up stuff
			JsonObject*	object = NULL;
			JsonArray*	array;
			int			n;
			bool		b;
			std::string	str;
		}	m_data;
	
};
