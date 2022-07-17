#pragma once

#include <string>
#include <vector>
#include <optional>

class Storage {
	public:
		virtual void write(const std::string& key, const std::vector<char>& content) = 0;
		virtual std::optional<std::vector<char>> read(const std::string& key) = 0;
		// true if removed, false if not present
		virtual bool remove(const std::string& key) = 0;
		virtual ~Storage() {}
};
