#include "../state.h"
#include <iostream>

using namespace std;
using namespace state;

State::State():cursor(10,10,2){ // call a specific constructor
    round=1;
    endGame=false;
    curPlayerID=1;
    nbOfPlayers=1;

}
State::~State(){}

//getters
