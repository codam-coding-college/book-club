#include "storage_proxy.hpp"
#include "json.hpp"
#include "json_parse.hpp"
#include <cmath>

using json::Json;

StorageProxy::StorageProxy(const std::string& ip, short port)
: connection(net::connect(ip, port)) {}

StorageProxy::~StorageProxy() {}

/*
Cache */

std::optional<std::vector<char>> StorageProxy::check_cache(const std::string& key) {
	auto it = cache.find(key);
	if (it == cache.end()) {
		return {};
	}
	return it->second;
}

void StorageProxy::add_cache(const std::string& key, const std::vector<char>& content) {
	if (keys.size() >= CACHE_SIZE) {
		const auto& to_remove = keys.front();
		cache.erase(to_remove);
		keys.pop_front();
	}
	keys.push_back(key);
	cache[key] = content;
}

void StorageProxy::delete_cache(const std::string& key) {
	// key is still present in keys deque but that's not too big of a deal
	// it costs some extra space but this still solves cache invalidation
	cache.erase(key);
}

/*
Command JSON format:
{
	"command": "GET" | "SET" | "DELETE",
	"key": STRING,
	[ "content": STRING ]
}
*/

/*
Response JSON format:
{
	"code": StatusCode,
	[ "content": STRING ]
}
*/

static bool double_eq(double a, double b) {
	static constexpr double EPSILON = 1.0e-6;
	return fabs(a - b) < EPSILON;
}

static bool is_ok(const Json& response) {
	if (response.get_type() != json::Type::Object) {
		return false;
	}
	const auto& object = response.get_object();
	auto it = object.find("code");
	return it != object.end() && it->second->get_type() == json::Type::Number && double_eq(it->second->get_num(), 200.0);
}

void StorageProxy::write(const std::string& key, const std::vector<char>& content) {
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
	std::cout << "Response ";
	response.print(std::cout, true);
	delete_cache(key);
}

std::optional<std::vector<char>> StorageProxy::read(const std::string& key) {
	auto cache_result = check_cache(key);
	if (cache_result.has_value()) {
		return cache_result.value();
	}
	Json::ObjectType object;
	object["command"] = std::unique_ptr<Json>(new Json { std::string {"GET"} });
	object["key"] = std::unique_ptr<Json>(new Json { key });
	Json data { std::move(object) };
	data.print(connection, false);
	connection.flush();
	Json response = json_parse::parse(connection);
	std::cout << "Response ";
	response.print(std::cout, true);
	if (!is_ok(response)) {
		return {};
	}
	auto it = response.get_object().find("content");
	if (it == response.get_object().end() || it->second->get_type() != json::Type::String) {
		return {};
	}
	std::vector<char> body { it->second->get_string().begin(), it->second->get_string().end() };
	add_cache(key, body);
	return body;
}

bool StorageProxy::remove(const std::string& key) {
	Json::ObjectType object;
	object["command"] = std::unique_ptr<Json>(new Json { std::string {"DELETE"} });
	object["key"] = std::unique_ptr<Json>(new Json { key });
	Json data { std::move(object) };
	data.print(connection, false);
	connection.flush();
	Json response = json_parse::parse(connection);
	std::cout << "Response ";
	response.print(std::cout, true);
	delete_cache(key);
	return is_ok(response);
}
