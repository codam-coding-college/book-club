#include "storage.hpp"
#include "storage_proxy.hpp"
#include "mrlog.hpp"
#include <iostream>

static std::vector<char> read_content(std::istream& input) {
	std::vector<char> result;
	input >> std::ws;
	while (input.good()) {
		std::string buffer;
		std::getline(input, buffer);
		if (buffer.empty()) {
			break;
		}
		result.insert(result.end(), buffer.begin(), buffer.end());
		result.push_back('\n');
	}
	return result;
}

static void print_content(const std::vector<char>& content) {
	for (char c: content) {
		std::cout << c;
	}
}

static void str_to_upper(std::string& s) {
	for (char& c: s) {
		c = toupper(c);
	}
}

static void print_intro() {
	mrlog::info("** Commands: **");
	mrlog::info("GET [KEY]");
	mrlog::info("SET [KEY]");
	mrlog::info("DELETE [KEY]");
	mrlog::info("QUIT");
}

// GET [KEY]
// SET [KEY]
// DELETE [KEY]
static void read_commands(std::istream& input, Storage& storage) {
	print_intro();
	while (input.good()) {
		std::string command;
		std::string key;
		input >> command;
		str_to_upper(command);
		// artistic branching
		if (command == "GET") {
			input >> key;
			auto content = storage.read(key);
			if (content.has_value()) {
				print_content(content.value());
			} else {
				mrlog::warn("not found: {}", key);
			}
		} else if (command == "SET") {
			input >> key;
			mrlog::info("write content until empty line");
			auto content = read_content(input);
			storage.write(key, content);
			mrlog::info("created: {}", key);
		} else if (command == "DELETE") {
			input >> key;
			if (storage.remove(key)) {
				mrlog::info("deleted: {}", key);
			} else {
				mrlog::info("not found: {}", key);
			}
		} else if (command == "QUIT") {
			break;
		} else {
			mrlog::error("invalid command: {}", command);
		}
	}
}

int main() {
	StorageProxy storage { "127.0.0.1", 3000 };
	read_commands(std::cin, storage);
	return 0;
}
