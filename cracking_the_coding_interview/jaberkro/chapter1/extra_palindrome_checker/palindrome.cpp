#include <iostream>

bool isPalindrome(std::string input)
{
    int rtl = input.length() - 1;

    for (int ltr = 0; ltr < rtl; ltr++)
    {
        if (input[ltr] == ' ')
            continue;
        while (input[rtl] == ' ')
            rtl--;
        if (input[ltr] != input[rtl])
        {
            std::cout << input.length() << std::endl;
            return (false);
        }
        rtl--;
    }
    return (true);
}

std::string toLower(std::string input)
{
    for (size_t i = 0; i < input.length(); i++)
    {
        if (input[i] >= 65 && input[i] <= 90)
            input[i] += 32;
    }
    return (input);
}

void displayUsage(void)
{
    std::cout << "Usage: ./palindromeChecker <your palindrome>" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        displayUsage();
        return (1);
    }
    try
    {
        if (isPalindrome(toLower(argv[1])))
            std::cout << "[" << argv[1] << "]: is a palindrome" << std::endl;
        else
            std::cout << "[" << argv[1] << "]: is not a palindrome" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << " not a valid char" << std::endl;
        displayUsage();
        return (1);
    }
    return (0);
}

/*
    Palindrome checker:
    Check if the input is a palindrome or not
*/

/*
    Big O notation:
    O(N / 2)
    O(N)
*/

/*
    Explanation:
    - First change the string to lowercase.
    - For each char in the first half (spaces are skipped), check is the same index from the back is the same char
*/
