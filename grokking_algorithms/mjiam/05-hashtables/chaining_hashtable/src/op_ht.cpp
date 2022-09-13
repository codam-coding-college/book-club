#include "op_ht.hpp"

OpHashTable::OpHashTable(size_t initial_capacity) : capacity(initial_capacity) {
	_table = new list< pair<string,int> >[capacity];
}

OpHashTable::~OpHashTable() {}

void	OpHashTable::AddElement(string const& op_str, int op_code) {
	size_t	hashval = Hash(op_str);

	_table[hashval].emplace(_table[hashval].end(), op_str, op_code);
}

void	OpHashTable::DeleteElement(string const& op_str) {
	size_t	index = Hash(op_str);
	auto i = _table[index].begin();

	for (; i != _table[index].end(); i++) {
		if ((*i).first == op_str)
			break;
	}
	if (i != _table[index].end())
		_table[index].erase(i);
}

int	OpHashTable::GetElementVal(string const& op_str) {
	size_t index = Hash(op_str);

	for (auto i = _table[index].begin(); i != _table[index].end(); i++) {
		if ((*i).first == op_str)
			return (*i).second;
	}
	return -1;
}

size_t	OpHashTable::Hash(string const& op_str) {
	size_t hashval = 0;

	for (size_t i = 0; op_str[i]; i++) {
		hashval = op_str[i] + 31 * hashval;
	}
	return (hashval % capacity);
}
