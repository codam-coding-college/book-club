/*
char** ft_split(const char* src, char delim);

Input Partitions:
SRC:
	- src == NULL [EXCEPTIONAL]
	- src is EMPTY [EXCEPTIONAL]
	- src has length 1 [EXCEPTIONAL]
	- src has length > 1
DELIM:
	- delim is the null terminator [EXCEPTIONAL]
	- delim is any other character

Tests:
	- exceptional cases mentioned above once
	- src contains no delim
	- src contains only delim
	- src contains one delim
	- src contains more than one delim
	- src contains delim at the start
	- src contains delim at the end
*/
