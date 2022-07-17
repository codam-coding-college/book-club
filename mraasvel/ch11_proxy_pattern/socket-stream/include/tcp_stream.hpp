#pragma once

#include "socket_buffer.hpp"
#include <iostream>

namespace net {

class TcpStream: public std::iostream {
	public:
		TcpStream(const TcpStream& other) = delete;
		TcpStream& operator=(const TcpStream& other) = delete;

		TcpStream();
		TcpStream(Socket&& socket);
		TcpStream(TcpStream&& other);
		TcpStream& operator=(TcpStream&& other);
		~TcpStream();

	private:
		SocketBuffer buffer;
};

}
