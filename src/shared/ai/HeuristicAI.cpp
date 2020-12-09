#include "HeuristicAI.h"
#include "engine.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>


using namespace ai;
using namespace std;
using namespace state;
using namespace engine;



HeuristicAI::HeuristicAI(engine::Engine& myEngine, int nbplayers){
    this->nbplayers = nbplayers;
}





void HeuristicAI::run(engine::Engine& engine){

    // personnage attaquable ?
    std::vector<std::unique_ptr<Player>>&  listPlayer = engine.getState().getListPlayers();

    //for (perso : listPlayer){
    //    if (perso.)
    //}

    // Sinon, déplacement vers le personnage le plus proche et attaque



}





