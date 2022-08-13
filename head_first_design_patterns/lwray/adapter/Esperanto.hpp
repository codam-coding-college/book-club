#ifndef ESPERANTO_CPP
# define ESPERANTO_CPP

#include <iostream>

class Esperanto {
public:
    virtual ~Esperanto() {};

    void saluton() const{
        std::cout << "Saluton kiel vi fartas?\n";
    };

    void prezenti(const char* name) const{
        std::cout << "Mia nomo estas " << name << std::endl;
    }
};

#endif