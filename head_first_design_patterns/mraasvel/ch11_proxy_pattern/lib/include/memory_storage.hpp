#pragma once

#include "storage.hpp"
#include <unordered_map>

class MemoryStorage: public Storage {
	public:
		~MemoryStorage();

		void write(const std::string& key, const std::vector<char>& content);
		std::optional<std::vector<char>> read(const std::string& key);
		bool remove(const std::string& key);

	private:
		std::unordered_map<std::string, std::vector<char>> storage;
};
