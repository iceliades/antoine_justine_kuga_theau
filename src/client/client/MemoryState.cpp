#include "MemoryState.h"
#include "state.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace state;
using namespace client;


MemoryState::MemoryState(state::State& myState) : memory(myState){
}

void MemoryState::loadState(state::State& myState){

    State* newState = new state::State();

    // joueur 1
    myState.getListCharacters(1);



    // le clone des personnages
    for (size_t i = 0; i < myState.getListCharacters(1).size(); i++)
    {
       

        

        unique_ptr<Character> newChar(new Character(*characters[i]->clone()));
        newState->characters.push_back(move(newChar));
    }
    
    // map
    for(auto& line : map){
        vector<unique_ptr<MapCell>> clonedLine;
        for(auto& cell : line){
            if(cell->isSpace()){
                SpaceMapCell* smc = (SpaceMapCell*)cell.get()->clone();
                unique_ptr<MapCell> upmc(new SpaceMapCell(*smc));
                clonedLine.push_back(move(upmc));
            } else {
                ObstacleMapCell* omc = (ObstacleMapCell*)cell.get()->clone();
                unique_ptr<MapCell> upmc(new ObstacleMapCell(*omc));
                clonedLine.push_back(move(upmc));
            }
        }
        s->map.push_back(move(clonedLine));
    }

    s->actualAction = actualAction;
    s->cursor = *cursor.clone();
    s->end = end;
    s->mode = mode;
    s->turn = turn;
    s->turnOwner = turnOwner;
    s->winner = winner;
    for (size_t i = 0; i < observers.size(); i++)
    {
        s->registerObserver(observers[i]);
    }
    
    MementoState m{*s};
    return m;
}
}
