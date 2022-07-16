#pragma once

#include "storage.hpp"
#include "memory_storage.hpp"
#include "net.hpp"
#include <unordered_map>
#include <deque>

class StorageProxy: public Storage {
	public:
		// constructor throws network exception
		StorageProxy(const std::string& ip, short port);
		~StorageProxy();

		void write(const std::string& key, const std::vector<char>& content);
		std::optional<std::vector<char>> read(const std::string& key);
		bool remove(const std::string& key);

	private:
		std::optional<std::vector<char>> check_cache(const std::string& key);
		void add_cache(const std::string& key, const std::vector<char>& content);
		void delete_cache(const std::string& key);

	private:
		static constexpr size_t CACHE_SIZE = 1 << 8; // 2^8

	private:
		net::TcpStream connection;
		std::unordered_map<std::string, std::vector<char>> cache; // key -> content
		std::deque<std::string> keys; // LRU cache
};
