#ifndef FRENCH_CPP
# define FRENCH_CPP

#include <iostream>

class French {
public:
    virtual ~French() {};

    void salut() const{
        std::cout << "Bonjour, comment ça va?\n";
    };

    void présenter(const char* name) const{
        std::cout << "Je m'appelle " << name << std::endl;
    }
};

#endif