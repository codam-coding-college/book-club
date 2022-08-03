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

int main() {
	string file_content = GetFileContents("./config.json");
	auto start_of_content = file_content.begin();
	json::Parser parser(start_of_content, file_content.end());
	auto product = parser.Produce();
	auto object = product->Finalize();
	cout << object->ToString() << "\n";

	//! ew
	delete(product);
	delete(object);
}
