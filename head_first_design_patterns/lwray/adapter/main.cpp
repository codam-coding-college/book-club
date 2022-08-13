#include "English.hpp"
#include "French.hpp"
#include "Esperanto.hpp"
#include "FrenchAdapter.hpp"
#include "EsperantoAdapter.hpp"

void ClientCode(const English& target) {
    target.greeting();
    target.introduce("Hector");
}

int main(){
    English english;
    FrenchAdapter french_adapter;
    EsperantoAdapter esperanto_adapter;

    ClientCode(english);

    std::cout << "\nThrough French adapter:  \n";
    ClientCode(french_adapter);

    std::cout << "\nThrough Esperanto adapter:  \n";
    ClientCode(esperanto_adapter);
}