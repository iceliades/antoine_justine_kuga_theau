#include "DeepAI.h"

using namespace std;
using namespace ai;


DeepAI::DeepAI(engine::Engine& myEngine, int nbPlayers) :  PlayerNumber(nbPlayers),
CurrState(myEngine.getState()){
    //this->CurrState = myEngine.getState();
}


DeepAI::~DeepAI(){
    delete &CurrState;
}



void DeepAI::run(engine::Engine& myEngine){

    
}


