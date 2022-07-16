#include "memory_storage.hpp"
#include "tcp_listener.hpp"
#include "json.hpp"
#include "json_parse.hpp"
#include "mrlog.hpp"

using json::Json;

enum class StatusCode {
	Ok = 200,
	BadRequest = 400,
	NotFound = 404,
	InternalServerError = 500
};

/*
Response JSON format:
{
	"code": StatusCode,
	[ "content": STRING ]
}
*/

Json make_response(StatusCode code, const std::optional<std::vector<char>>& content) {
	Json::ObjectType object;
	object["code"] = std::unique_ptr<Json> { new Json { static_cast<double>(code) } };
	if (content.has_value()) {
		object["content"] = std::unique_ptr<Json> {
			new Json {
				std::string { content.value().begin(), content.value().end() }
			}
		};
	}
	return Json { std::move(object) };
}

void send_response(net::TcpStream& connection, StatusCode code, const std::optional<std::vector<char>>& content) {
	make_response(code, content).print(connection, false);
	connection.flush();
}

/*
Command JSON format:
{
	"command": "GET" | "SET" | "DELETE",
	"key": STRING,
	[ "content": STRING ]
}
*/

static bool is_type(const Json::ObjectType& object, const std::string& key, json::Type type) {
	auto it = object.find(key);
	return !(it == object.end() || it->second->get_type() != type);
}

Json process_command(const Json& request) {
	if (request.get_type() != json::Type::Object) {
		throw std::runtime_error("bad request");
	}
	const auto& object = request.get_object();
	if (!is_type(object, "command", json::Type::String) || !is_type(object, "key", json::Type::String)) {
		throw std::runtime_error("bad request");
	}
	const std::string& command = object.at("command")->get_string();
	// const std::string& key = object.at("key")->get_string();
	if (command == "GET") {
		return make_response(StatusCode::InternalServerError, {});
	} else if (command == "SET") {
		return make_response(StatusCode::InternalServerError, {});
	} else if (command == "DELETE") {
		return make_response(StatusCode::InternalServerError, {});
	} else {
		return make_response(StatusCode::BadRequest, {});
	}
}

int handle_connection(net::TcpStream connection, Storage&) {
	try {
		Json request = json_parse::parse(connection);
		request.print(std::cout, true);
		// 1. parse request
		Json response = process_command(request);
		response.print(connection, false);
		connection.flush();
	} catch (std::exception& e) {
		send_response(connection, StatusCode::BadRequest, {});
		return 1;
	}
	return 0;
}

int run_server(const std::string& addr, short port, Storage& storage) {
	net::TcpListener listener;
	if (listener.init(addr, port) == net::NetResult::Error) {
		return -1;
	}
	mrlog::info("accepting connections on {}:{}", addr, port);
	while (true) {
		net::TcpStream connection = listener.accept();
		mrlog::info("received connection, handling...");
		handle_connection(std::move(connection), storage);
	}
	return 0;
}

int main() {
	const std::string ip = "127.0.0.1";
	const short port = 3000;
	MemoryStorage storage {};
	if (run_server(ip, port, storage) == -1) {
		return 1;
	}
	return 0;
}
