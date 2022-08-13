#pragma once

#include "tcp_stream.hpp"
#include <string>
#include <exception>

namespace net {

enum class NetResult {
	Ok,
	Error
};

using std::string;

class NetException: public std::exception {
	public:
		NetException(const std::string& reason);
		virtual const char* what() const noexcept;
	
	private:
		std::string reason;
};

TcpStream connect(const string& address, short port);

}
