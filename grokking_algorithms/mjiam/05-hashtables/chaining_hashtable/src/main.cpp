#include "op_ht.hpp"

enum	e_op_code
{
	SWAP_A = 0,
	SWAP_B,
	SWAP_2,
	PUSH_A,
	PUSH_B,
	ROT_A,
	ROT_B,
	ROT_2,
	REVR_A,
	REVR_B,
	REVR_2
};

string	OpCodeToString(int op_code) {
	switch (op_code) {
		case -1:
			return "NO SUCH ELEMENT IN TABLE";
		case SWAP_A:
			return "SWAP_A";
		case SWAP_B:
			return "SWAP_B";
		case SWAP_2:
			return "SWAP_2";
		case PUSH_A:
			return "PUSH_A";
		case PUSH_B:
			return "PUSH_B";
		case ROT_A:
			return "ROT_A";
		case ROT_B:
			return "ROT_B";
		case ROT_2:
			return "ROT_2";
		case REVR_A:
			return "REVR_A";
		case REVR_B:
			return "REVR_B";
		case REVR_2:
			return "REVR_2";
		default:
			return "UNKNOWN OPCODE";
	};
}

int	main() {
	OpHashTable	hashtable;

	cout << "== Inserting sa, sb, ra ==\n";
	hashtable.AddElement("sa", SWAP_A);
	hashtable.AddElement("sb", SWAP_B);
	hashtable.AddElement("ra", ROT_A);
	cout << "sa -> " << OpCodeToString(hashtable.GetElementVal("sa")) << endl;
	cout << "sb -> " << OpCodeToString(hashtable.GetElementVal("sb")) << endl;
	cout << "ra -> " << OpCodeToString(hashtable.GetElementVal("ra")) << endl;
	cout << "== Removing sb ==\n";
	hashtable.DeleteElement("sb");
	cout << "== Inserting rra ==\n";
	hashtable.AddElement("rra", REVR_A);
	cout << "sa -> " << OpCodeToString(hashtable.GetElementVal("sa")) << endl;
	cout << "sb -> " << OpCodeToString(hashtable.GetElementVal("sb")) << endl;
	cout << "ra -> " << OpCodeToString(hashtable.GetElementVal("ra")) << endl;
	cout << "rra -> " << OpCodeToString(hashtable.GetElementVal("rra")) << endl;
	return 0;
}
