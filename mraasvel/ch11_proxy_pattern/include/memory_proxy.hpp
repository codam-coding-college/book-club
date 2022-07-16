#pragma once

#include "storage.hpp"
#include "memory_storage.hpp"
#include "net.hpp"

class MemoryStorageProxy: public Storage {
	public:
		// constructor throws network exception
		MemoryStorageProxy(const std::string& ip, short port);
		~MemoryStorageProxy();

		void write(const std::string& key, const std::vector<char>& content);
		std::optional<std::vector<char>> read(const std::string& key);
		bool remove(const std::string& key);

	private:
		net::TcpStream connection;
};
