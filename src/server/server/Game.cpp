#include "Game.h"
#include <memory>
#include <map>
#include <vector>
#include <set>

using namespace server;
using namespace std;
using std::unique_ptr;
using std::map;
using std::vector;

Game::Game (){}

Player* Game::getPlayerById (int id){
    auto it = players.find(id);
    if (it == players.cend())
        return nullptr;
    return it->second.get();
};


void Game::removePlayer (int id){
    auto it = players.find(id);
    if (it == players.end())
        return;
    players.erase(it);
}


int Game::addPlayer (std::unique_ptr<Player> newPlayer){
    int id = players.size();
    players.insert(std::make_pair(id, std::move(newPlayer)));
    id += 1;
    return id;
}

