#ifndef ENGLISH_CPP
# define ENGLISH_CPP

#include <iostream>

class English {
public:
    virtual ~English() {};

    virtual void greeting() const{
        std::cout << "Hello, how are you?\n";
    };

    virtual void introduce(std::string name) const{
        std::cout << "My name is " << name << std::endl;
    }
};

#endif