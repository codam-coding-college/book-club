#include "json.hpp"
#include "json_parse.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <functional>

struct Options {
	Options(): filename(nullptr) {}
	char* filename;
	bool readable;
};

enum ParseArgsResult {
	Error,
	Quit,
	Continue,
};

static void print_help() {
	std::cout << "Options\n";
	std::cout << "\t--help\n";
	std::cout << "\t-f --file FILE ; read from file FILE\n";
	std::cout << "\t-r --readable ; human readable output\n";
}

static ParseArgsResult parse_help(int, char*[], int*, Options*) {
	print_help();
	return ParseArgsResult::Quit;
}

static ParseArgsResult parse_readable(int, char *[], int*, Options* options) {
	options->readable = true;
	return ParseArgsResult::Continue;
}

static ParseArgsResult parse_file(int argc, char* argv[], int* index, Options* options) {
	if (argc == *index + 1) {
		return ParseArgsResult::Error;
	}
	*index += 1;
	options->filename = argv[*index];
	return ParseArgsResult::Continue;
}

static ParseArgsResult parse_args(int argc, char *argv[], Options* options) {
	using FlagFunction = std::function<ParseArgsResult(int, char*[], int*, Options*)>;
	argc--; argv++;

	const std::unordered_map<std::string, FlagFunction> flags {
		std::make_pair("--help", parse_help),
		std::make_pair("-r", parse_readable),
		std::make_pair("--readable", parse_readable),
		std::make_pair("-f", parse_file),
		std::make_pair("--file", parse_file),
	};
	for (int i = 0; i < argc; i++) {
		auto it = flags.find(argv[i]);
		if (it == flags.end()) {
			return ParseArgsResult::Error;
		}
		switch ((it->second)(argc, argv, &i, options)) {
			case ParseArgsResult::Error:
				return ParseArgsResult::Error;
			case ParseArgsResult::Quit:
				return ParseArgsResult::Quit;
			case ParseArgsResult::Continue:
				break;
		}
	}
	return ParseArgsResult::Continue;
}

int main(int argc, char *argv[]) {
	Options options;
	switch (parse_args(argc, argv, &options)) {
		case ParseArgsResult::Error:
			std::cerr << "Error: invalid arguments: --help for options\n";
			return 1;
		case ParseArgsResult::Quit:
			return 0;
		case ParseArgsResult::Continue:
			break;
	}
	try {
		if (options.filename != nullptr) {
			std::ifstream ifs { options.filename };
			if (!ifs.is_open()) {
				std::cerr << "Error: failed to open file: " << options.filename << "\n";
				return 1;
			}
			auto json = json_parse::parse(ifs);
			json.print(std::cout, options.readable);
		} else {
			auto json = json_parse::parse(std::cin);
			json.print(std::cout, options.readable);
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}
