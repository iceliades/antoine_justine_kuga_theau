#include "Command_Client_DAI.h"
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include <unistd.h>
#include <iostream>

using namespace client;
using namespace state;
using namespace render;
using namespace engine;
using namespace std;



Command_Client_DAI::Command_Client_DAI() {
}
Command_Client_DAI::~Command_Client_DAI(){
}

void Command_Client_DAI::execute() {
   // Random_ai vs Random_ai

    srand(time(NULL));// Init random generator

    Engine DAIEngine; // No confusion to engine packgage
    DAIEngine.getState().setMode("random_ai");
    DAIEngine.getState().initPlayers();
    DAIEngine.getState().initCharacters();
    DAIEngine.getState().initMapCell();


    sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
    StateLayer stateLayer (DAIEngine.getState(),window);
    stateLayer.initTextureArea(DAIEngine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    DAIEngine.getState().registerObserver(ptr_stateLayer);

    bool booting=true;

    // Init ai
    ai::DeepAI deepai(DAIEngine,2,1);
    ai::RandomAI randomAi;
    randomAi.setNbplayers(1); // PLayer ID 2


    while (window.isOpen()){
        sf::Event event;
        if( booting){
            stateLayer.draw(window);
            DAIEngine.update();
            booting=false;
        }
        if(DAIEngine.getState().getCurPlayerID()==2){
            cout<<"**********************BEFORE DEEP AI EXE************************"<<endl;
            if(DAIEngine.getState().getEndGame()==false)
                deepai.run(DAIEngine);
                usleep(500000);
            cout<<"**********************AFTER DEEP AI EXE************************"<<endl;
        }else
        {
            cout << "**********************You are just before RAI execution**********************" <<endl;
            if(DAIEngine.getState().getEndGame()==false)
                randomAi.run(DAIEngine);
            cout << "**********************You are just after RAI execution**********************" <<endl;
        }
        StateEvent stateEvent(ALLCHANGED);
        DAIEngine.getState().notifyObservers(stateEvent,DAIEngine.getState());
        // at the close event seems not working
        // will see later for use this
        if(DAIEngine.getState().getEndGame()==true){
            window.close();
        }
            
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

    }
}