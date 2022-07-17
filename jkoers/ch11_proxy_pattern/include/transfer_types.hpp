#pragma once
#include "rpc.hpp"

struct Request : public Transfer_object {
	Request(int number) : number(number) {}
	Request() {}

  public:
	std::vector<uint8_t> serialize() const {
		std::vector<uint8_t> buffer;
		buffer.resize(sizeof(number));
		std::memcpy(buffer.data(), &number, sizeof(number));
		return buffer;
	}
	void deserialize(const std::vector<uint8_t>& data) {
		assert(data.size() == sizeof(number));
		std::memcpy(&number, data.data(), sizeof(number));
	}

	int number;
};

struct Response {
  public:
	Response(int number) : number(number) {}
	Response() {}

	std::vector<uint8_t> serialize() const {
		std::vector<uint8_t> buffer;
		buffer.resize(sizeof(number));
		std::memcpy(buffer.data(), &number, sizeof(number));
		return buffer;
	}

	void deserialize(const std::vector<uint8_t>& data) {
		assert(data.size() == sizeof(number));
		std::memcpy(&number, data.data(), sizeof(number));
	}

	int number;
};
