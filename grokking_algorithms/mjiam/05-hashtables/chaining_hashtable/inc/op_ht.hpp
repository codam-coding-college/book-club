#ifndef OP_HT_HPP
#define OP_HT_HPP

#include <list>
#include <iostream>

using namespace std;

class	OpHashTable {
	public:
		OpHashTable(size_t initial_capacity = 256);
		~OpHashTable();

		size_t	capacity;

		void	AddElement(string const& op_str, int op_code);
		void	DeleteElement(string const& op_str);
		int		GetElementVal(string const& op_str);

	private:
		list< pair<string,int> >	*_table;

		size_t	Hash(string const& op_str);
};

#endif /* OP_HT_HPP */
