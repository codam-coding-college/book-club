#pragma once
#include <cstdint>
#include <string>
#include <vector>
#define MAX_BUFFER_SIZE 1024

struct Socket {
  public:
	Socket();
	Socket(int fd);
	Socket(Socket&& other);
	Socket& operator=(Socket&& other);

	void	read(std::vector<uint8_t>& buffer, size_t size);
	void	write(const std::vector<uint8_t>& buffer);

	int		fd;

	~Socket();
	Socket(const Socket& other) = delete;
	Socket& operator=(const Socket& other) = delete;

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

class Transfer_object {
  public:
	virtual std::vector<uint8_t> serialize() const = 0;
	virtual void				 deserialize(const std::vector<uint8_t>& data) = 0;
};

template <typename T_request, typename T_response>
class RPC_client {
  public:
	RPC_client(const std::string& host, uint16_t port) : socket(host, port){};

	T_response call(const T_request& request) {
		this->write_buffer = request.serialize();
		socket.write(this->write_buffer);

		this->read_buffer.resize(this->write_buffer.size());
		socket.read(this->read_buffer, this->write_buffer.size());

		T_response out;
		out.deserialize(this->read_buffer);
		return out;
	};

  private:
	Client_socket		 socket;
	std::vector<uint8_t> read_buffer;
	std::vector<uint8_t> write_buffer;
};

template <typename T_request, typename T_response>
class RPC_server {
  public:
	RPC_server(uint16_t port) : socket(port){};

	void respond(T_response (*handler)(const T_request& request)) {
		Socket client = socket.accept();
		this->read_buffer.resize(MAX_BUFFER_SIZE);
		client.read(read_buffer, read_buffer.size());

		T_request request;
		request.deserialize(read_buffer);
		T_response response = handler(request);
		write_buffer = response.serialize();
		client.write(write_buffer);
	}

  private:
	Server_socket		 socket;
	std::vector<uint8_t> read_buffer;
	std::vector<uint8_t> write_buffer;
};
