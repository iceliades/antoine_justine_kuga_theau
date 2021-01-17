/*#include "engine.h"
#include "render.h"
#include "state.h"
#include "client.h"
//#include "Client_Network.h"
#include "ai.h"
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <pthread.h>

using namespace state;
using namespace engine;
using namespace render;
using namespace std;
using namespace client;
using namespace ai;

bool runEngine = false;
bool runThread = true;
bool booting = true;

void threadEngine(Engine *ptr)
{
    while (runThread)
    {
        usleep(1000); // not overcharge cpu
        if (runEngine)
        {
            ptr->update();
            runEngine = false;
        }
    }
}

Client::Client_Network(int port, std::string &url, sf::RenderWindow &window, std::string mode)
{
    this->windows=windows;
    this->mode=mode;
    this->url=url;

    engine.getState().setMode(mode);
    engine.getState().initPlayers();
    engine.getState().initCharacters();
    engine.getState().initMapCell();

    ai_1 = new HeuristicAI(engine, 1); 
    ai_2 = new DeepAI(engine, character);
  


    engine.multithread = true;

    
    engine.registerObserver(this);

}





// Getters

std::string getMode(){
    return this->mode;
}

std::string getUrl(){
    return this->url;
}

int getPort(){
    return this->port;
}

engine::Engine getEngine(){
    return this->engine;
}

getWindow(){
    return this->window();
}

/*

void Client::run()
{
    StateLayer stateLayer(engine.getState(), window);
    stateLayer.initTextureArea(engine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);
    std::thread th(threadEngine, &engine);
    while (!engine.getState().getEndGame())
    {
        if (booting)
        {
            stateLayer.draw(window);
            booting = false;
        }

        ai_1->run(engine);
        ai_2->run(engine);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                engine.getState().setEndGame(true);
                cout << "\tWindow closed" << endl;
                break;
            }
        }
    }
    runThread = false;
    th.join();
}

void Client::engineUpdating() {
    runEngine = true;
    usleep(150000);
}

void Client::engineUpdated() {};

const std::string Client::getMode() {
    return mode;
}
*/
