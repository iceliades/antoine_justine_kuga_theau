#include "DeepAI.h"
#include "state.h"
#include "engine.h"

using namespace std;
using namespace ai;


DeepAI::DeepAI(engine::Engine& engine, int nbPlayers) :  PlayerNumber(nbPlayers),CurrState(engine.getState()){
    //this->CurrState = myEngine.getState();
}


DeepAI::~DeepAI(){
    delete &CurrState;
}



void DeepAI::run(engine::Engine& myEngine){

    
}


