#include "Command_Client_RAI.h"
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

using namespace client;
using namespace std;


Command_Client_RAI::Command_Client_RAI() {
}
Command_Client_RAI::~Command_Client_RAI(){
}
void Command_Client_RAI::execute() {
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
    ai::RandomAI randomAi1;
    ai::RandomAI randomAi2;

    randomAi1.setNbplayers(1); // PLayer ID 1
    randomAi2.setNbplayers(2); // PLayer ID 2
    // Init some characters stuffs to be  faster
    for(int i=0; i<myEngine.getState().getListPlayers().size(); i++){
        for(int j=0;j<myEngine.getState().getListCharacters(i).size(); j++){
            myEngine.getState().getListCharacters(i)[j]->setNewHealth(50);
            myEngine.getState().getListCharacters(i)[j]->setPrecision(15,15,15,15);// precision to 1
            myEngine.getState().getListCharacters(i)[j]->setDodge(8,8);
            if( i==1){
                Position pos{2+j,4};
                myEngine.getState().getListCharacters(i)[j]->setPosition(pos);

            }else{

                Position pos1{2+j,6};
                myEngine.getState().getListCharacters(i)[j]->setPosition(pos1);

            }

        }
    }

    while (window.isOpen()){
        sf::Event event;
        if( booting){
            stateLayer.draw(window);
            booting=false;
        }
        if(myEngine.getState().getCurPlayerID()==1){
            //unique_ptr<Command> ptr_ft(new Finish_Turn_Command());
            //myEngine.addCommand(move(ptr_ft));myEngine.update();
            if(myEngine.getState().getEndGame()==false)
                randomAi1.run(myEngine);
        }else
        {
            if(myEngine.getState().getEndGame()==false)
                randomAi2.run(myEngine);
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
