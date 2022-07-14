#ifndef URI_PARSER_HPP
#define URI_PARSER_HPP

#include "state_parser.hpp"

enum URIStates {
	u_Start = 0
};

class URIParser : public StateParser<URIStates> {

};

#endif // URI_PARSER_HPP