#include "Player.h"

using namespace server;
using namespace std;

Player::Player(std::string name, bool free):name(name), free(free) {
}

// getters
std::string Player::getName(){
    return this->name;
}

bool Player::getFree(){
    return free;
}

//setters
void Player::setName(std::string name) {
    this->name = name;
    return ;
}
void Player::setFree(bool free){
    this->free = free;
    return ;
}