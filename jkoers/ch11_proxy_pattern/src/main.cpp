#include "rpc.hpp"
#include <iostream>
#include <string>

void print_error() {
	std::cout << "Usage: server <port>" << std::endl;
	std::cout << "Usage: client <IPV4 address> <port>" << std::endl;
}

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		print_error();
		return 1;
	}
	else if (!strcmp(argv[1], "server") && argc == 3) {
		Server_socket server(atoi(argv[2]));
		server.accept();
		std::cout << "accepted" << std::endl;
	}
	else if (!strcmp(argv[1], "client") && argc == 4) {
		Client_socket client(argv[2], atoi(argv[3]));

		std::cout << "client connected" << std::endl;
	}
	else {
		print_error();
		return 1;
	}
	return 0;
}
