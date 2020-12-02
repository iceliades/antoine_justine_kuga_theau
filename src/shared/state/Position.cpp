#include "Position.h"
#include <iostream>

using namespace std;
namespace state {

    Position::Position() {
        x=0;
        y=0;
    }

    Position::Position(int x, int y){
        this->x=x;
        this->y=y;
    }

    Position::~Position() {

    }

    int Position::getX(){ return x;}
    int Position::getY(){ return y;}

    void Position::setX(int x){ this->x=x; }
    void Position::setY(int y){ this->y=y;}

    // If 2 elements are in the same position
    bool Position::equals( Position& position){
        return((position.getX()==x) && (position.getY()==y));
    }

    int Position::distance(Position& position){
        return abs(position.getX()-x)+abs(position.getY() -y);
    }

    std::vector<Position> Position::getNearPositions(){

        vector<Position> result;

        Position south{this->getX(), this->getY() + 1};
        Position north{this->getX(), this->getY() - 1};
        Position west{this->getX() - 1, this->getY()};
        Position east{this->getX() + 1, this->getY()};

        // coin en bas à gauche
        if (this->getY() == 0){
            if (this->getX() == 0){
                west.setX(0);
                west.setY(0);
            }
            if (this->getX() == 26){
                east.setX(0);
                east.setY(0);
            }
            north.setX(0);
            north.setY(0);
        }

        if (this->getY() == 24){
            if (this->getX() == 0){
                west.setX(0);
                west.setY(0);
            }
            if (this->getX() == 26){
                east.setX(0);
                east.setY(0);
            }
            south.setX(0);
            south.setY(0);
        }



        result.push_back(move(south));
        result.push_back(move(east));
        result.push_back(move(north));
        result.push_back(move(west));

        return result;
    }

}