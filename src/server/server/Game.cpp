#include "Game.h"


using namespace server;
using namespace std;


Game::Game () : engine("myGame"){}

Game::~Game(){
    delete this->Players;
}

Player::Player(string name, bool free) : name(name), free(free)
{
}


