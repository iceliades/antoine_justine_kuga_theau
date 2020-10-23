#include "Element.h"

using namespace state;
namespace state
{
    Element :: Element(){ 
        name= "ok";
        position= Position();
        tileCode=1;
    };
    std::string Element::getName(){
        return name;
    }


    
} // namespace state
