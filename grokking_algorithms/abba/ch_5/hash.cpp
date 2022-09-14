#include "hash.hpp"

#define DICTIONARY "dictionary/big_file.txt"
int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "error\n";
		return 1;
	}
	char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;
	bool loaded = load(dictionary);
	if (!loaded) {
		std::cout << "Could not load " <<  dictionary << std::endl;
		return 1;
	}

}