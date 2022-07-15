#include "Parse.hpp"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc > 2)
	{
		std::cout << "argument to long" << std::endl;
		return 1;
	}
	Parse	parse("default.config");
	parse.parse();
}