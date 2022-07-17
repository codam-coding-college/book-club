#include "rpc.hpp"
#include "transfer_types.hpp"
#include <iostream>
#include <map>
#include <string>

void print_error() {
	std::cout << "Usage: server <port>" << std::endl;
	std::cout << "Usage: client <IPV4 address> <port>" << std::endl;
}

// compute result
Response computer(const Request& request) {
	const Response response(request.number * 2);
	return response;
}

void server(uint16_t port) {
	while (true) {
		RPC_server<Request, Response> server(port);
		server.respond(computer);
		std::cout << "accepted" << std::endl;
	}
}

std::map<int, int> cache; // TODO: user Request() and Response instead of int
//
Response proxy(const Request& request, RPC_client<Request, Response>& client) {
	if (cache.find(request.number) != cache.end()) {
		std::cout << "Cache hit" << std::endl;
		return Response(cache[request.number]);
	}

	std::cout << "Cache miss" << std::endl;
	Response response = client.call(request);

	cache[request.number] = response.number;
	return response;
}

void client(const std::string& host, uint16_t port) {
	while (true) {
		RPC_client<Request, Response> client(host, port);
		Request						  request;
		std::cout << "\nEnter number: " << std::ends;
		std::cin >> request.number;

		auto	 start = std::chrono::high_resolution_clock::now();

		Response response = proxy(request, client);

		auto	 end = std::chrono::high_resolution_clock::now();
		auto	 duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Got response: " << response.number << " in " << duration.count() << " microseconds" << std::endl;
	}
}

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		print_error();
		return 1;
	}
	else if (!strcmp(argv[1], "server") && argc == 3) {
		server(atoi(argv[2]));
	}
	else if (!strcmp(argv[1], "client") && argc == 4) {
		client(argv[2], atoi(argv[3]));
	}
	else {
		print_error();
		return 1;
	}
	return 0;
}
