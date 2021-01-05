#include "engine.h"
#include "render.h"
#include "state.h"
#include "client.h"
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
/*
bool canRunEngine = false;
bool runFunctionCalled = true;
bool once = true;

void threadEngine(Engine *ptr)
{
    while (runFunctionCalled)
    {
        usleep(1000);
        if (canRunEngine)
        {
            ptr->update();
            canRunEngine = false;
        }
    }
}

Client::Client(sf::RenderWindow &window, std::string mode) {
    this->mode = mode;

    std::string map_path = (mode == "test") ? "../../../res/map_v0.txt" : "res/map_v0.txt";
    engine.getState().initMapCell();
    engine.getState().initCharacters();
    engine.registerObserver(this);
    //engine.multithread = true;


}

void Client::run()
{
    StateLayer stateLayer(engine.getState(), window);
    stateLayer.initTextureArea(engine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);
    sf::Music backMusic;
    std::string music = (mode == "test") ? "../../../res/epic_music.wav" : "res/epic_music.wav";
    if (backMusic.openFromFile(music))
    {
        backMusic.setVolume(40);
        backMusic.setLoop(true);
        backMusic.play();
    }
    std::thread th(threadEngine, &engine);
    while (!engine.getState().getEndGame())
    {
        if (once)
        {
            stateLayer.draw(window);
            once = false;
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
    runFunctionCalled = false;
    th.join();
}*/