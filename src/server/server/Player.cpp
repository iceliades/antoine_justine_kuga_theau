#include "Player.h"

using namespace server;
using namespace std;

Player::Player(std::string name, bool free) {
    this->name=name;
    this->free=free;
}
