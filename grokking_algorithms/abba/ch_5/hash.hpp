#ifndef HASH_HPP
#define HASH_HPP

#define LENGTH 40
#include <cstring>
#include <ctype>

typedef struct node {
	char word[LENGTH + 1];
	struct node *next;
}				node;

// Number of bucket
const unsigned N = 26^3;
node *_table[N];

class hash_table {
private:
	unsigned int _count;

public:
	hash_table() : _count(0) { }
	//return true if the word is already there
	bool check(const char *word) {
		node *tmp;

		tmp = _table[hash(word)];
		while (tmp) {
			if (strcmp(tmp->word, word) == 0) {
				return true;
			}
			tmp = tmp->next;
		}
		return false;
	}

	//hash word to number
	unsigned int hash(const char *word) {
		int c;

		unsigned long hash = 5381;
		while ((c = *word++)) {
			c = tolower(c);
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		}
		return hash % N;
	}

	// Loads dictionary into memory
	bool load(const char *dictionary) {
		FILE *input = fopen(dictionary, "r");
		if (input == NULL) {
			return false;
		}
		//read string from file
		node *new_word;
		char word [LENGTH + 1];
		while (fscanf(input, "%s", word) != EOF)
		{
			new_word = malloc(sizeof(node));
			if (new_word == NULL) {
				return false;
			}
			//copy a string to another
			strcpy(new_word->word, word);
			new_word->next = NULL;
			//get hash table
			int index = hash(word);
			if (_table[index] == NULL) {
				_table[index] = new_word;
			} else {
				new_word->next = _table[index];
				_table[index] = new_word;
			}
			_count++;
		}
		fclose(input);
		return true;
	}

	// Returns number of words in dictionary if loaded, else 0 if not yet loaded
	unsigned int size(void) {
		return _count;
	}

	// Unloads dictionary from memory
	bool unload(void) {
		node *cursor = NULL, *tmp = NULL;
		for (int i = 0; i < N; i++) {
			cursor = _table[i];
			while (cursor != NULL) {
				tmp = cursor;
				cursor = cursor->next;
				free(tmp);
			}
		}
		return true;
	}
};


#endif