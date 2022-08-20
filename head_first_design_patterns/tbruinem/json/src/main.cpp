#include "parser.hpp"
#include "parsed_json.hpp"
#include "element.hpp"

#include <iostream>
#include "fstream"
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

string GetFileContents(string file_path) {
	auto ss = ostringstream{};
	ifstream input_file(file_path);
	if (!input_file.is_open()) {
		exit(EXIT_FAILURE);
	}
	ss << input_file.rdbuf();
	return ss.str();
}

string GetFilePath(int argc, char**argv) {
	if (argc != 2) {
		//!Get absolute path to the default config file
		string executable_path = argv[0];
		auto slash_idx = executable_path.find_last_of('/');
		auto directory_path = executable_path.substr(0, slash_idx+1);
		return directory_path + "config.json";
	}
	return string(argv[1]);
}

int main(int argc, char **argv) {
	string file_content = GetFileContents(GetFilePath(argc, argv));
	auto start_of_content = file_content.begin();
	json::Parser parser(start_of_content, file_content.end());
	auto product = parser.Produce();
	auto object = product->Finalize();
	cout << object->ToString(0) << "\n";

	delete(product);
	delete(object);
}
