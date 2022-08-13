#include "tcp_stream.hpp"
#include "mrlog.hpp"
#include <utility>

namespace net {

TcpStream::TcpStream() {}
TcpStream::TcpStream(Socket&& socket): std::iostream(&buffer), buffer(std::move(socket)) {}
TcpStream::TcpStream(TcpStream&& other): std::iostream(&buffer), buffer(std::move(other.buffer)) {}

TcpStream::~TcpStream() {}

TcpStream& TcpStream::operator=(TcpStream&& other) {
	if (this == &other) {
		return *this;
	}
	buffer = std::move(other.buffer);
	return *this;
}

}
