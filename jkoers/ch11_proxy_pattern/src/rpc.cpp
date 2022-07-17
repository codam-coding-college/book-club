#include "rpc.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

[[noreturn]] void exit_with_perror(const std::string& msg) {
	::perror(msg.c_str());
	exit(EXIT_FAILURE);
}

Socket::Socket() {
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd < 0)
		exit_with_perror("socket failed");
}

Socket::Socket(int fd) : fd(fd) {}

Socket::Socket(Socket&& other) : fd(other.fd) {
	other.fd = -1;
}

Socket& Socket::operator=(Socket&& other) {
	if (this == &other) {
		return *this;
	}
	this->close();
	fd = other.fd;
	other.fd = -1;
	return *this;
}

void Socket::read(std::vector<uint8_t>& buffer, size_t size) {
	buffer.reserve(size);
	ssize_t n = ::read(this->fd, buffer.data(), buffer.size());
	// if (n != (ssize_t)size) // TODO: buffering
	// 	exit_with_perror("read failed");
	buffer.resize((size_t)n);
}

void Socket::write(const std::vector<uint8_t>& buffer) {
	ssize_t n = ::write(this->fd, buffer.data(), buffer.size());
	if (n != (ssize_t)buffer.size()) // TODO: buffering
		exit_with_perror("write failed");
}

void Socket::close() {
	if (fd < 0)
		return;

	if (::close(fd) < 0)
		exit_with_perror("could not close socket");
	fd = -1;
}

Socket::~Socket() {
	this->close();
}

Server_socket::Server_socket(uint16_t port) {
	const int on = 1;
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) < 0)
		exit_with_perror("setsockopt() failed");

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (::bind(this->fd, (struct sockaddr*)&address, sizeof(address)) < 0)
		exit_with_perror("bind failed");

	if (::listen(this->fd, 128) < 0)
		exit_with_perror("listen failed");
}

Socket Server_socket::accept() {
	const int fd = ::accept(this->fd, NULL, NULL); // TODO: address etc
	if (fd < 0)
		exit_with_perror("accept failed");
	return Socket(fd);
}

// client

Client_socket::Client_socket(const std::string& host, uint16_t port) {
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0)
		exit_with_perror("inet_pton failed");

	if (::connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		exit_with_perror("connect failed");
}
