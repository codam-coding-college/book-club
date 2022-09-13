#include "hash_set.hpp"
#include <string>
#include <cassert>

struct StringHash {
	size_t operator()(const std::string& key) const {
		return key.size();
	}
};

int main() {
	grokking::HashSet<std::string, StringHash> set;

	assert(set.find("1234") == false);

	set.insert("1234");
	set.insert("2345");
	set.insert("234");
	set.insert("");
	set.insert("1098234123401230948");
	set.insert("1234567890");

	assert(set.find("1234") == true);
	assert(set.find("2345") == true);

	set.erase("1234");
	assert(set.find("1234") == false);
	set.print();
	return 0;
}
