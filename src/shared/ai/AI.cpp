#include "AI.h"
#include "state.h"
#include <stdlib.h>
#include <unistd.h>

using namespace ai;
using namespace state;
using namespace std;

AI::AI(int pn){
    this->nbplayers = pn;
}

int AI::getNbplayers (){
    return nbplayers;
}

void AI::setNbplayers (int pn){
    if(pn == 1 || pn == 2){
        nbplayers = pn;
    }
}
