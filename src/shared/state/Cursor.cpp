#include "Cursor.h"
#include <iostream>

using namespace std;
using namespace state;


Cursor::Cursor(int x, int y, int p_tileCode)
{
    lastPosition.setX(x);
    lastPosition.setY(y);
    position.setX(x);
    position.setY(y);
    tileCode=p_tileCode;
    visible=false;

}
bool Cursor::isMapCell(){
    return false;

}

void Cursor::move(Position& destination){
    lastPosition=position;
    position= destination;
}
bool Cursor::getVisible(){
    return visible;
}

void Cursor::setVisible(bool visibility){
    visible=visibility;
}

Position& Cursor::getLastPosition(){
    return lastPosition; // return a ref
}

Cursor* Cursor::clone(){
    return new Cursor(*this);
}