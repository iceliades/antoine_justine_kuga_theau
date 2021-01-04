#include "Element.h"
#include <typeinfo>

namespace state {

    
    Element::Element() {
        name = "Element";         
    }

    Element::~Element() {
    }

    
    int Element::getTileCode(){ return tileCode;}
    std::string Element::getName() { return name;}
    Position& Element::getPosition(){
        // return ref
        return position;
    }


    void Element::setName(const std::string &name) { this->name = name;}
    void Element::setTileCode(int p_tileCode){  tileCode=p_tileCode;}
    void Element::setPosition(const Position& position){
        this->position= position;
    }
    
    bool Element::equals(Element &other){
        return (typeid(other).name()==name && position.equals(other.getPosition()));
    }
    
}
