#include "Command_Client_HAI.h"
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include <unistd.h>

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

    Engine myEngine; // No confusion to engine packgage
    myEngine.getState().setMode("random_ai");
    myEngine.getState().initPlayers();
    myEngine.getState().initCharacters();
    myEngine.getState().initMapCell();


    sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
    StateLayer stateLayer (myEngine.getState(),window);
    stateLayer.initTextureArea(myEngine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    myEngine.getState().registerObserver(ptr_stateLayer);

    bool booting=true;

    // Init ai
    ai::DeepAI deepai(myEngine,1);
    ai::RandomAI randomAi;
    randomAi.setNbplayers(2); // PLayer ID 2


    while (window.isOpen()){
        sf::Event event;
        if( booting){
            stateLayer.draw(window);
            myEngine.update();
            booting=false;
        }
        if(myEngine.getState().getCurPlayerID()==1){
            if(myEngine.getState().getEndGame()==false)
                deepai.run(myEngine);
        }else
        {
            if(myEngine.getState().getEndGame()==false)
                randomAi.run(myEngine);
        }
        // at the close event seems not working
        // will see later for use this
        if(myEngine.getState().getEndGame()==true){
            window.close();
        }
            
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

    }
}