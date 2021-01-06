#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
#include <memory>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#include <state.h>
#include "render.h"
#include "engine.h"
#include "ai.h"
#include "client.h"

using namespace client;
using namespace state;
using namespace render;
using namespace engine;
using namespace std;

using namespace client;
using namespace std;

Command_Client_Thread::Command_Client_Thread() {

}
void Command_Client_Thread::execute() {

    sf::RenderWindow window(sf::VideoMode((25 * 32) + 256, (20 * 32) + 32, 32), "map");

    client::Client client(window,"game");

    while (window.isOpen()) {
        client.run();
        sleep(2);
        window.close();
    }
}