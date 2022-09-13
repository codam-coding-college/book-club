#include "hash_set.hpp"
#include <string>
#include <cassert>

struct StringHash {
	size_t operator()(const std::string& key) const {
		size_t hash = 7;
		for (unsigned char ch: key) {
			hash = hash * 31 + ch;
		}
		return hash;
	}
};

int main() {
	grokking::HashSet<std::string, StringHash> set;

	assert(set.find("json") == false);

	set.insert("hashtable");
	set.insert("maarten");
	set.insert("json");
	set.insert("hashset");
	set.insert("rust");
	set.insert("parser");

	assert(set.find("rust") == true);
	assert(set.find("json") == true);

	set.erase("json");
	assert(set.find("json") == false);
	set.print();
	return 0;
}
