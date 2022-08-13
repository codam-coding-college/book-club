#ifndef ESPERANTOADAPTER_CPP
# define ESPERANTOADAPTER_CPP

#include <iostream>
#include "English.hpp"
#include "French.hpp"
#include "Esperanto.hpp"

class EsperantoAdapter : public English, public Esperanto {
public:
    EsperantoAdapter() {};
    void greeting() const{
        saluton();
    };

    virtual void introduce(std::string name) const{
        prezenti(name.c_str());
    }
};

#endif