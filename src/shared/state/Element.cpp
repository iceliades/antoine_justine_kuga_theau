#include "Element.h"

namespace state {

    Element::Element() {

         name = "Nom";
         position = Position();
         tileCode = 1;
    }

    Element::~Element() {

    }

    void Element::setTileCode(int x){
        this->tileCode = x;
    };

    int Element::getTileCode(){
        int x = tileCode;
        return x;
    };

    void Element::setName(const std::string &name) {
        this->name = name;
    }

    std::string Element::getName() {
        return name;
    }

}