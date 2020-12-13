#include "Command_Client_Render.h"
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include "client.h"

using namespace client;
using namespace state;
using namespace render;
using namespace std;


Command_Client_Render::Command_Client_Render() {
}
Command_Client_Render::~Command_Client_Render(){
}
void Command_Client_Render::execute(){
    State state;
    state.setMode("render");
    state.setCurAction(state::MOVING);
    state.initPlayers();
    state.initCharacters();
    state.initMapCell();

    sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
    StateLayer stateLayer (state,window);


    stateLayer.initTextureArea(state);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        stateLayer.draw(window);


    }
}
