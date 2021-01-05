#include "Command_Client_Play.h"
#include "state.h"
#include "engine.h"
#include "render.h"
#include <string>
#include <fstream>

using namespace client;
using namespace std;
using namespace Json;

Command_Client_Play::Command_Client_Play(){}
Command_Client_Play::~Command_Client_Play(){}

void Command_Client_Play::execute(){
   
    engine::Engine myEngine;    
    myEngine.getState().initPlayers();
    myEngine.getState().initCharacters();
    myEngine.getState().initMapCell();

    sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
    render::StateLayer stateLayer (myEngine.getState(),window);
    stateLayer.initTextureArea(myEngine.getState());

    render::StateLayer *ptr_stateLayer = &stateLayer;
    myEngine.getState().registerObserver(ptr_stateLayer);

    std::string replayPath="res/replay.txt";
    bool booting=true;

    /*//Reading Json
    std::ifstream cmdFile(replayPath);
    Json::Reader reader;
    Json::Value cmd;
    if(!reader.parse(cmdFile,cmd)){
    }*/
    
/*
    while (window.isOpen()){
        sf::Event event;
        if( booting){
            stateLayer.draw(window);
            booting=false;
        }
        
        


        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
    }*/



}

