#pragma once
#include <cstdint>
#include <string>

struct Socket {
  public:
	Socket();
	Socket(int fd);
	Socket(Socket&& other);
	Socket& operator=(Socket&& other);
	~Socket();

	Socket(const Socket& other) = delete;
	Socket& operator=(const Socket& other) = delete;

	int		fd;

  private:
	void close();
};

class Server_socket : public Socket {
  public:
	Server_socket() = delete;
	Server_socket(uint16_t port);

	Socket accept();
};

class Client_socket : public Socket {
  public:
	Client_socket() = delete;
	Client_socket(const std::string& host, uint16_t port);
	// ~Client_socket();
};
