#include "Command_Client_Rollback.h"
#include "client.h"
#include "ai.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <unistd.h>

using namespace client;
using namespace engine;
using namespace render;
using namespace std;


Command_Client_Rollback::Command_Client_Rollback() {
}
Command_Client_Rollback::~Command_Client_Rollback(){
}
void Command_Client_Rollback::execute() {
    
    srand(time(NULL));// Init random generator

    Engine myEngine; // No confusion to engine packgage
    myEngine.getState().initPlayers();
    myEngine.getState().initCharacters();
    myEngine.getState().initMapCell();

    sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
    StateLayer stateLayer (myEngine.getState(),window);
    stateLayer.initTextureArea(myEngine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    myEngine.getState().registerObserver(ptr_stateLayer);
    
    bool booting=true;
    Caretaker ct;
    MemoryState* mem= new MemoryState(myEngine.getState());
    ai::HeuristicAI hai1(myEngine,1);
    ai::HeuristicAI hai2(myEngine,2);
    int nbRoundToRollback=6; // each player will play 3 time
    if (window.isOpen()){
        sf::Event event;
        if( booting){
            stateLayer.draw(window);
            booting=false;
        }
        
        for(int i=0;i<nbRoundToRollback;i++){
            mem= new MemoryState(mem->loadState(myEngine.getState()));
            ct.addMemory(*mem);
            cout<< i<<endl;
            if(!myEngine.getState().getEndGame()){
                if(myEngine.getState().getCurPlayerID()==1)
                    hai1.run(myEngine);
                else
                    hai2.run(myEngine);
            }

        }
        for(int i=ct.getSavedMemories().size()-1;i>0;i++){
            mem->recover(myEngine.getState());
        }
    }

}