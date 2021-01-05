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


}