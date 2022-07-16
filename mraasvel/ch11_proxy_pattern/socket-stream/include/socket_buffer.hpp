#pragma once

#include "socket.hpp"
#include <streambuf>

namespace net {

class SocketBuffer: public std::streambuf {
	public:
		SocketBuffer(const SocketBuffer& other) = delete;
		SocketBuffer& operator=(const SocketBuffer& other) = delete;

		SocketBuffer();
		SocketBuffer(Socket&& socket);
		SocketBuffer(SocketBuffer&& other);
		SocketBuffer& operator=(SocketBuffer&& other);
		virtual ~SocketBuffer();

		virtual int_type underflow();
		virtual int_type overflow(int_type ch = traits_type::eof());
		virtual int sync();

	private:
		void fail();
		int fill();

	private:
		static constexpr size_t BUFFER_SIZE = 1024 * 4;

	private:
		Socket socket;
		char input[BUFFER_SIZE];
		char output[BUFFER_SIZE];
};

}
