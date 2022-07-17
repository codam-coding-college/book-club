#pragma once

#include "net.hpp"
#include "socket.hpp"
#include "tcp_stream.hpp"

namespace net {

class TcpListener {
	public:
		NetResult init(const string& ip, short port);
		// simple blocking accept
		TcpStream accept() const;

	private:
		Socket listener;
};

}
