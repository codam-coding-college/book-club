#include "uri_parser.hpp"

void	URIParser::Parse(string const& uri_string) {
	_path.clear();
	_query.clear();
	ParseString(uri_string);
}

void	URIParser::PrintURIParts() {
	cout << "Input: " << input << endl;
	cout << "Path: " << GetPath() << " | Query: " << GetQuery() << endl;
	cout << endl; 
}

InTypes	URIParser::GetTokenType(char uri_char) {
	switch (uri_char) {
		case '/':
			return i_Slash;
		case '?':
			return i_Question;
		case '#':
			return i_Hash;
		case '\0':
			return i_EOL;
		default:
			if (string(PCHAR).find(uri_char) != string::npos)
				return i_PChar;
			else
				return i_Other;
	}
}

// Pushes buffer to appropriate URI field when valid ending token indicates
// transition out of current (path/query) state to next or final state.
void	URIParser::PushBuffertoField() {
	switch (cur_state) {
		case u_Path:
			_path += buffer;
			break;
		case u_Query:
			_query += buffer.substr(1);
			break;
		default:
			return ;
	}
	buffer.clear();
}

URIState	URIParser::GetNextState(size_t pos) {
	InTypes token_type = GetTokenType(input[pos]);

	URIState next_state = LookUpTable[cur_state][token_type];
	if (next_state > cur_state)
		PushBuffertoField();
	return next_state;
}

void	URIParser::CheckStateInvalid() const {
	if (cur_state == u_Invalid)
		throw BadURIException();
}

// If terminating state is indicated, stops loop.
bool	URIParser::CheckStateDone() {
	return (cur_state == u_Done);
}

// Checks if URI string is greater than 8kb (limit of most web servers)
void	URIParser::CheckPreParse() {
	if (input.size() > 8192)
		throw BadURIException();
}

// Checks if there's illegal characters after terminating char.
void	URIParser::CheckAfterParse(size_t pos) {
	if (cur_state == u_Done && pos < input.size() - 1)
		throw BadURIException();
}