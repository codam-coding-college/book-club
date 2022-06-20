#ifndef FRENCHADAPTER_CPP
# define FRENCHADAPTER_CPP

#include <iostream>
#include "English.hpp"
#include "French.hpp"

class FrenchAdapter : public English, public French {
public:
    FrenchAdapter() {};
    void greeting() const{
        salut();
    };

    virtual void introduce(std::string name) const{
        présenter(name.c_str());
    }
};

#endif