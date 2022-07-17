#include "socket_buffer.hpp"
#include <sys/socket.h>

namespace net {

SocketBuffer::SocketBuffer() {}
SocketBuffer::SocketBuffer(Socket&& socket): socket(std::move(socket)) {}
SocketBuffer::SocketBuffer(SocketBuffer&& other): SocketBuffer(std::move(other.socket)) {}

SocketBuffer& SocketBuffer::operator=(SocketBuffer&& other) {
	if (this == &other) {
		return *this;
	}
	socket = std::move(other.socket);
	return *this;
}

SocketBuffer::~SocketBuffer() {
	sync();
}

SocketBuffer::int_type SocketBuffer::underflow() {
	// this is where we return data from the input buffer, reading from the connection if there is no data
	if (gptr() == egptr()) {
		// empty buffer or finished reading
		ssize_t bytes = fill();
		if (bytes <= 0) {
			fail();
			return traits_type::eof();
		}
		setg(input, input, input + bytes);
	}
	return *gptr();
}

SocketBuffer::int_type SocketBuffer::overflow(int_type ch) {
	// this is where we write data into an output buffer, flushing if there is no space
	if (pptr() == epptr()) {
		if (pptr() == nullptr) {
			setp(output, output + BUFFER_SIZE);
		} else if (sync() < 0) {
			fail();
			return traits_type::eof();
		}
	}
	*pptr() = ch;
	pbump(1); // kind of surprised that this was necessary
	traits_type::not_eof(ch);
	return ch;
}

int SocketBuffer::sync() {
	// flush output
	if (pptr() == pbase()) {
		return 0;
	}
#ifdef __APPLE__
	if (send(socket.fd, output, pptr() - pbase(), 0) < 0) {
		return -1;
	}
#else
	if (send(socket.fd, output, pptr() - pbase(), MSG_NOSIGNAL) < 0) {
		return -1;
	}
#endif
	setp(output, output + BUFFER_SIZE);
	return 0;
}

int SocketBuffer::fill() {
	return recv(socket.fd, input, sizeof(input), 0);
}

void SocketBuffer::fail() {
	setg(nullptr, nullptr, nullptr); // get area
	setp(nullptr, nullptr); // put area
}

}
