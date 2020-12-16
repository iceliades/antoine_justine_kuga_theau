#include "AI.h"


using namespace ai;
using namespace std;


 AI::AI(int nbplayers){
    this->nbplayers = nbplayers; // playerID
}

int AI::getNbplayers (){
    return nbplayers;
}

void AI::setNbplayers (int newNb){
    nbplayers = newNb;
}
