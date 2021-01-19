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

}

Game::~Game() {}

Player* Game::getIdPlayer (int id){
    auto it = players.find(id);
    if (it == players.cend())
        return nullptr;
    return it->second.get();
};

const std::map<int, std::unique_ptr<Player>>& Game::getPlayers() const {
    return players;
}

void Game::modifyPlayer (int id, std::unique_ptr<Player> newPlayer){
    players[id] = move(newPlayer);
    if (id > gameId) gameId = id;
}

void Game::removePlayer (int id){
    auto it = players.find(id);
    if (it == players.end())
        return;
    players.erase(it);
}

int Game::addPlayer (std::unique_ptr<Player> newPlayer){
    int id = gameId;
    players.insert(std::make_pair(id, std::move(newPlayer)));
    gameId += 1;
    return id;
}