#include "AI.h"


using namespace ai;
using namespace std;

 AI::AI(int nbplayers){
    this->nbplayers = nbplayers;
}

int AI::getNbplayers (){
    return nbplayers;
}

void AI::setNbplayers (int newNb){
    if(newNb == 1 || newNb == 2){
        nbplayers = newNb;
    }
}
