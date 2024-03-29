#include <iostream>
#include <string>

bool isUnique(std::string input)
{
    for (size_t i = 0; i < input.length(); i++)
    {
        for (size_t j = i + 1; j < input.length(); j++)
        {
            if (i < j && input[i] == input[j])
                return (false);
        }
    }
    return (true);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./isUnique <your input>" << std::endl;
        return (1);
    }
    std::cout << "[" << argv[1] << "]";
    if (isUnique(argv[1]))
        std::cout << " has all unique characters" << std::endl;
    else
        std::cout << " does not have all unique characters" << std::endl;
    return (0);
}

/* 
    1.1 Is Unique:
    Implement an algorithm to determine if a string has all unique characters. 
    What if you cannot use additional data structures? 
*/

/* 
    Compilation:
    c++ -Wall -Werror -Wextra ex01.cpp -o isUnique
*/

/* 
    Big O Notation:
    N * (N - 1)
    O(N^2)
*/
