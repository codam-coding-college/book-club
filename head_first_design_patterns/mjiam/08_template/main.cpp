#include <iostream>
#include "uri_parser.hpp"

int	main() {
	URIParser	parser;

	try {
		parser.Parse("/hello/world");
		parser.PrintURIParts();
		assert(parser.GetPath() == "/hello/world" && parser.GetQuery().empty());

		parser.Parse("/hello.txt?q=val1");
		parser.PrintURIParts();
		assert(parser.GetPath() == "/hello.txt" && parser.GetQuery() == "q=val1");

		parser.Parse("/hello.com?q=val1#");
		parser.PrintURIParts();
		assert(parser.GetPath() == "/hello.com" && parser.GetQuery() == "q=val1");

		parser.Parse("/path/to/query?param1=value&param2=value2");
		parser.PrintURIParts();
		assert(parser.GetPath() == "/path/to/query" && parser.GetQuery() == "param1=value&param2=value2");

		parser.Parse("/hello .com?q=val1"); // invalid uri
	}
	catch (URIParser::BadURIException& e) {
		cout << e.what() << endl;
	}
	return 0;
}