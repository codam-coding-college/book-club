#include "memory_storage.hpp"

MemoryStorage::~MemoryStorage() {}

void MemoryStorage::write(const std::string& key, const std::vector<char>& content) {
	storage[key] = content;
}

std::optional<std::vector<char>> MemoryStorage::read(const std::string& key) {
	auto it = storage.find(key);
	if (it == storage.end()) {
		return {};
	}
	return it->second;
}

bool MemoryStorage::remove(const std::string& key) {
	size_t n = storage.erase(key);
	return n == 1;
}
