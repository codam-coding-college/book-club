#include "rpc.hpp"
#include "transfer_types.hpp"
#include <iostream>
#include <string>

void print_error() {
	std::cout << "Usage: server <port>" << std::endl;
	std::cout << "Usage: client <IPV4 address> <port>" << std::endl;
}

Response handler(const Request& request) {
	const Response response(request.number * 2);
	return response;
}

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		print_error();
		return 1;
	}
	else if (!strcmp(argv[1], "server") && argc == 3) {
		while (true) {
			RPC_server<Request, Response> server(atoi(argv[2]));
			server.respond(handler);
			std::cout << "accepted" << std::endl;
		}
	}
	else if (!strcmp(argv[1], "client") && argc == 4) {
		RPC_client<Request, Response> client(argv[2], atoi(argv[3]));
		Response					  response = client.call(Request(42));
		std::cout << "got response " << response.number << std::endl;
	}
	else {
		print_error();
		return 1;
	}
	return 0;
}
