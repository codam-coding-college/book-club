#include "Json.hpp"

Json::Json(std::string file_name)
{
	std::cout << "config filename: " << file_name << std::endl;
	_file.open(file_name, std::ios::in);
	if (!_file)
	{
		std::cout << "wrong file" << std::endl;
		exit(1);
	}

//	std::string line;
//	while (std::getline(_file, line))
//	{
//		std::cout << line << std::endl;
//	}
}

std::fstream &Json::getFile()
{
	return _file;
}

Json::~Json()
{

}