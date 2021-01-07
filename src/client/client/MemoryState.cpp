#include "MemoryState.h"
#include "state.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace state;
using namespace client;


MemoryState::MemoryState(state::State& myState):memory(myState){

}
MemoryState::~MemoryState() {
    //delete memory;
}
state::State& MemoryState::getMemory(){
    return memory;
}

MemoryState MemoryState::loadState(state::State& myState){
    State* s = new State();
    s->initPlayers();
    //memory= new State();
    
    // save Character
    for(unsigned int i=0; i<myState.getListPlayers().size();i++){
        for(unsigned int j=0; j<myState.getListCharacters(i).size();j++){
            unique_ptr<Character> newChar(new Character(*myState.getListCharacters(i)[j]));
            s->getListCharacters(i).push_back(move(newChar));
        }
    }

    // save map
    for(auto& line : myState.getMap()){
        vector<unique_ptr<MapCell>> clonedLine;
        for(auto& cell : line){
            if(cell->isSpace()){
                SpaceMapTiles* smc = ((SpaceMapTiles*)cell.get())->clone();
                unique_ptr<MapCell> upmc(new SpaceMapTiles(*smc));
                clonedLine.push_back(move(upmc));
            } else {
                ObstacleMapTiles* omc = ((ObstacleMapTiles*)cell.get())->clone();
                unique_ptr<MapCell> upmc(new ObstacleMapTiles(*omc));
                clonedLine.push_back(move(upmc));
            }
        }
        s->getMap().push_back(move(clonedLine));
    }

    

    s->getCursor().setPosition(myState.getCursor().getPosition());
    s->getCursor().setTileCode(myState.getCursor().getTileCode());
    s->getCursor().setVisible(myState.getCursor().getVisible());
    s->setCurAction(myState.getCurAction());
    s->setEndGame(myState.getEndGame());
    s->setMode(myState.getMode());
    s->setRound(myState.getRound());
    s->setCurPlayerID(myState.getCurPlayerID());
    s->setGameWinner(myState.getGameWinner());
    
    for (size_t i = 0; i < myState.getObservers().size(); i++)
    {
        s->registerObserver(myState.getObservers()[i]);
    }
    MemoryState ms{*s};
    return ms;

}

void MemoryState::recover(state::State& myState){
    
    // characters
    for(unsigned int i=0; i<memory.getListPlayers().size();i++){
        myState.getListCharacters(i).clear(); // clear curState
        for(unsigned int j=0; j<memory.getListCharacters(i).size();j++){
            unique_ptr<Character> newChar(new Character(*memory.getListCharacters(i)[j]));
            myState.getListCharacters(i).push_back(move(newChar));
        }

    }
    // curState clear map
    myState.getMap().clear();
    for(auto& line : memory.getMap()){
        vector<unique_ptr<MapCell>> clonedLine;
        for(auto& cell : line){
            if(cell->isSpace()){
                SpaceMapTiles* smc = ((SpaceMapTiles*)cell.get())->clone();
                unique_ptr<MapCell> upmc(new SpaceMapTiles(*smc));
                clonedLine.push_back(move(upmc));
            } else {
                ObstacleMapTiles* omc = ((ObstacleMapTiles*)cell.get())->clone();
                unique_ptr<MapCell> upmc(new ObstacleMapTiles(*omc));
                clonedLine.push_back(move(upmc));
            }
        }
        myState.getMap().push_back(move(clonedLine));
    }
  
    myState.setCurAction(memory.getCurAction());
    myState.getCursor().setPosition(memory.getCursor().getPosition());
    myState.getCursor().setTileCode(memory.getCursor().getTileCode());
    myState.getCursor().setVisible(memory.getCursor().getVisible());
    myState.setEndGame(memory.getEndGame());
    myState.setMode(memory.getMode());
    myState.setRound(memory.getRound());
    myState.setCurPlayerID(memory.getCurPlayerID());
    myState.setGameWinner(memory.getGameWinner());

}