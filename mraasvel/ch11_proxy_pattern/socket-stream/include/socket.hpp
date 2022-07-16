#pragma once

#include <ostream>

namespace net {

/*
Owning class of a socket file descriptor.
*/
struct Socket {
	public:
		Socket();
		Socket(int fd);
		Socket(Socket&& other);
		Socket& operator=(Socket&& other);
		~Socket();

		Socket(const Socket& other) = delete;
		Socket& operator=(const Socket& other) = delete;

		int fd;
	
	private:
		void close_socket();
};

std::ostream& operator<<(std::ostream& out, const Socket& rhs);

}
