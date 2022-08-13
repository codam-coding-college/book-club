#include "net.hpp"
#include "mrlog.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>

namespace net {

NetException::NetException(const std::string& reason): reason(reason) {}

const char* NetException::what() const noexcept {
	return reason.c_str();
}

TcpStream connect(const string& address, short port) {
	Socket socket { ::socket(AF_INET, SOCK_STREAM, 0) };
	if (socket.fd < 0) {
		throw NetException { "failed to create socket" };
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(address.c_str());
	if (::connect(socket.fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
		throw NetException { "failed to connect to server" };
	}
	return TcpStream { std::move(socket) };
}

}
