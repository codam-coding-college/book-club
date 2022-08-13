#ifndef URI_PARSER_HPP
#define URI_PARSER_HPP

#include <exception>
#include <iostream>
#include <string>
#include "state_parser.hpp"

using namespace std;

#define ALPHA "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGIT "0123456789"
#define UNRESERVED ALPHA DIGIT "-._~"
#define SUBDELIM "!$&'()*+,;="
#define PCHAR UNRESERVED SUBDELIM ":@"

enum URIState {
	u_Invalid = -1,
	u_Start = 0,
	u_PathStart,
	u_Path,
	u_Query,
	u_Done
};

enum InTypes {
	i_Slash = 0,
	i_Question,
	i_PChar,
	i_Hash,
	i_EOL,
	i_Other
};

static URIState LookUpTable[5][6] = {
	//   /			?			PCh			#			\0			Other
	{u_PathStart,	u_Invalid,	u_Invalid,	u_Invalid,	u_Invalid,	u_Invalid}, // start
	{u_Invalid,		u_Query,	u_Path,		u_Invalid,	u_Done,		u_Invalid}, // PathStart
	{u_Path,		u_Query,	u_Path,		u_Invalid,	u_Done,		u_Invalid}, // path
	{u_Query,		u_Query,	u_Query,	u_Done,		u_Done,		u_Invalid} // query
};

// Simplified origin-form URI parser that doesn't deal with host component or percent-encoding.
class URIParser : public StateParser<URIState> {
	public:
		URIParser() {}
		~URIParser() {}

		void	Parse(string const& uri_string);
		void	PrintURIParts();
		string	GetPath() { return _path; }
		string	GetQuery() { return _query; }


		class BadURIException : public exception {
			public:
				virtual const char* what() const throw() {
					return ("Bad URI. Try again.");
				}
		};
	
	private:
		string	_path;
		string	_query;

		InTypes		GetTokenType(char uri_char);
		void		PushBuffertoField();

	protected:
		URIState	SetStartState() const { return u_Start; }
		URIState	GetNextState(size_t pos);
		void		CheckStateInvalid() const;
		bool		CheckStateDone();
		void		CheckPreParse();
		void		CheckAfterParse(size_t pos);
};

#endif /* URI_PARSER_HPP */
