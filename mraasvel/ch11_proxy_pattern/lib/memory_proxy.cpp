#include "memory_proxy.hpp"
#include "json.hpp"
#include "json_parse.hpp"

using json::Json;

MemoryStorageProxy::MemoryStorageProxy(const std::string& ip, short port)
: connection(net::connect(ip, port)) {}

MemoryStorageProxy::~MemoryStorageProxy() {}

/*
Command JSON format:
{
	"command": "GET" | "SET" | "DELETE",
	"key": STRING,
	[ "content": STRING ]
}
*/

void MemoryStorageProxy::write(const std::string& key, const std::vector<char>& content) {
	std::cout << "Set COMMAND\n";
	Json::ObjectType object;
	object["command"] = std::unique_ptr<Json>(new Json { std::string {"SET"} });
	object["key"] = std::unique_ptr<Json>(new Json { key });
	object["content"] = std::unique_ptr<Json>(new Json { std::string { content.begin(), content.end() } });

	// writing request
	Json data { std::move(object) };
	data.print(connection, false);
	connection.flush();

	// reading response
	Json response = json_parse::parse(connection);
	response.print(std::cout, true);
}

std::optional<std::vector<char>> MemoryStorageProxy::read(const std::string& key) {
	Json::ObjectType object;
	object["command"] = std::unique_ptr<Json>(new Json { std::string {"GET"} });
	object["key"] = std::unique_ptr<Json>(new Json { key });
	Json data { std::move(object) };
	data.print(std::cout, true);
	data.print(connection, false);
	connection.flush();
	// TODO: process response
	Json response = json_parse::parse(connection);
	response.print(std::cout, true);
	return {};
}

bool MemoryStorageProxy::remove(const std::string& key) {
	Json::ObjectType object;
	object["command"] = std::unique_ptr<Json>(new Json { std::string {"DELETE"} });
	object["key"] = std::unique_ptr<Json>(new Json { key });
	Json data { std::move(object) };
	data.print(connection, false);
	connection.flush();
	// TODO: process response
	Json response = json_parse::parse(connection);
	response.print(std::cout, true);
	return true;
}
