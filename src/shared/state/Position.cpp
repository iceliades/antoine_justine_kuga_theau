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
        return(position.getX()==x && position.getY()==y);
    }

    int Position::distance(Position& position){
        return abs(position.getX()-x)+abs(position.getY() -y);
    }

    std::vector<Position> Position::getNearPositions(){

	vector<Position> result;
	Position front{this->getX(), this->getY() + 1};
	Position back{this->getX(), this->getY() - 1};
	Position left{this->getX() - 1, this->getY()};
	Position right{this->getX() + 1, this->getY()};
	result.push_back(move(front));
	result.push_back(move(right));
	result.push_back(move(back));
	result.push_back(move(left));

	return result;
}

}