#include <iostream>

bool checkPalindromePermutation(std::string input)
{
    int alphabet = 0;
    int index = 0;

    for (size_t i = 0; i < input.length(); i++)
    {
        if (input[i] >= 97 && input[i] <= 122)
            index = input[i] - 97;
        else if (input[i] >= 65 && input[i] <= 90)
            index = input[i] - 65;
        else if (input[i] == ' ')
            continue ;
        else
        {
            std::cout << input[i] << ": invalid input" << std::endl;
            return (false);
        }
        alphabet = alphabet ^ (1 << index);
    }
    if ((alphabet & (alphabet - 1)))
        return (false);
    return (true);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./palindrome <your input as one string>" << std::endl;
        return (1);
    }
    if (checkPalindromePermutation(argv[1]) == true)
        std::cout << argv[1] << ": is a palindrome permutation" << std::endl;
    else
        std::cout << argv[1] << ": is not a palindrome permutation" << std::endl;
    return (0);
}

/* 
    1.4 Palindrome Permutation:
    Given a string, write a function to check if it is a permutation of a palin­drome.
    A palindrome is a word or  phrase that is the same forwards and backwards. 
    A permutation is a rearrangement of letters. 
    The palindrome does not need to be limited to just dictionary words. 
*/

/*
    Compilation:  
    c++ ex04.cpp -Wall -Wextra -Werror -o palindrome
*/

/*
    Big O Notation:
    O(N)
*/
