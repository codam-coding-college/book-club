#include "tcp_listener.hpp"
#include "socket.hpp"
#include "mrlog.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <cassert>

namespace net {

NetResult TcpListener::init(const string& ip, short port) {
	assert(listener.fd == -1);
	Socket sock { socket(AF_INET, SOCK_STREAM, 0) };
	if (sock.fd == -1) {
		mrlog::error("failed to create socket: {}", strerror(errno));
		return NetResult::Error;
	}
#ifdef __APPLE__
	const int enable = 1;
	// untested
	if (setsockopt(sock.fd, SOL_SOCKET, SO_REUSEADDR | SO_NOSIGPIPE, &enable, sizeof(int)) < 0) {
		mrlog::error("failed to set socket options: {}", strerror(errno));
		return NetResult::Error;
	}
#else
	const int enable = 1;
	if (setsockopt(sock.fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		mrlog::error("failed to set socket options: {}", strerror(errno));
		return NetResult::Error;
	}
#endif

	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	if (bind(sock.fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
		mrlog::error("failed to bind on interface {}:{}: {}", ip, port, strerror(errno));
		return NetResult::Error;
	}
	if (listen(sock.fd, 10) < 0) {
		mrlog::error("listen failed on interface {}:{}: {}", ip, port, strerror(errno));
		return NetResult::Error;
	}
	listener = std::move(sock);
	mrlog::info("new listening socket [{}] on {}:{}", listener.fd, ip, port);
	return NetResult::Ok;
}

// simple blocking accept
TcpStream TcpListener::accept() const {
	assert(listener.fd != -1);
	static constexpr int MAX_RETRIES = 3;

	int retries = 0;
	while (retries < MAX_RETRIES) {
		Socket connection = { ::accept(listener.fd, NULL, NULL) };
		if (connection.fd < 0) {
			retries += 1;
			mrlog::error("failed to accept connection, retrying...");
			continue;
		}
		return TcpStream { std::move(connection) };
	}
	throw NetException { "failed to accept connection" };
}

}
