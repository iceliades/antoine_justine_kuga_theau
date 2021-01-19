#include "engine.h"
#include "render.h"
#include "state.h"
#include "client.h"
#include "ai.h"
#include "Client_Network.h"

#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
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

Client_Network::Client_Network(int port, string &url, sf::RenderWindow &window, std::string mode) : window(window) {


    this->mode=mode;
    this->url=url;

    engine.getState().setMode(mode);
    engine.getState().initPlayers();
    engine.getState().initCharacters();
    engine.getState().initMapCell();
    
    engine.registerObserver(this);

}

void Client_Network::engineUpdated() {}

void Client_Network::engineUpdating() {

    for (size_t i = 0; i < engine.getCurrCommands().size(); i++)
    {
        Command *c = &(*engine.getCurrCommands()[i]);
        //putServerCommand(c);
    }
    cout << "engine updating" << endl;
    engine.update();
    usleep(150000);
}

engine::Engine Client_Network::getEngine() {}

std::string Client_Network::getMode() {
    return this->mode;
}

sf::RenderWindow & Client_Network::getWindow() {
    return window;
}
/*
void Client_Network::run() {

    StateLayer stateLayer(engine.getState(), window);
    stateLayer.initTextureArea(engine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);
    stateLayer.draw(window);
    std::thread th(threadEngine, &engine);
    while (!engine.getState().getEndGame())
    {
        if (!engine.getState().getEndGame())
        {
            StateEvent e(ALLCHANGED);
            engine.getState().notifyObservers(e, engine.getState());
        }
        if (display)
        {
            stateLayer.draw(window);
            //cout << "Turn " << engine.getState().getTurn() << endl;
            display = false;
        }
        //playerAI->setPlayerNumber(character);
        if (engine.getState().getTurnOwner() == character) // is my turn
        {
            // play
            playerAI->run(engine);
            sleep(2);
        }
        else
        {
            // while is not my turn, wait
            sf::Http http(url, port);
            sleep(1);
            // get commands from opponent passing my player number (1 or 2)
            sf::Http::Request request;
            request.setMethod(sf::Http::Request::Get);
            string uri = "/command";
            request.setUri(uri);
            request.setHttpVersion(1, 0);
            Json::Reader jsonReader;
            Json::Value commands;

            sf::Http::Response response = http.sendRequest(request);
            cout << response.getBody() << endl;
            if (jsonReader.parse(response.getBody(), commands))
            {
                // get and apply opponent commands
                getServerCommands(commands);
            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Fermeture de la fenetre
            if (event.type == sf::Event::Closed)
            {
                window.close();
                engine.getState().setEnd(true);
                cout << "\tWindow closed" << endl;
                break;
            }
        }
    }

    l2 = false;
    th.join();
}
*/