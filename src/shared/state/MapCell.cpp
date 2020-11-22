#include "MapCell.h"
#include <iostream>
#include "State.h"
using namespace std;
using namespace state;

bool MapCell::isMapCell(){
    return true;
}

int MapCell::isOccupied (State& state){
    
    // A faire
    unsigned int nbPlayers=  state.getListPlayers().size();
    for (unsigned int  j=0; j<nbPlayers; j++){
        for ( unsigned int i=0; i < state.getListCharacters(j).size();i++){
            if (position.equals(state.getListCharacters(j)[i]->getPosition())&& state.getListCharacters(j)[i]->getStatus()!=DEATH ){
                return i+ (j*state.getListCharacters(j).size()); // PlayerID * Index in ListCharacters
            }

        }     
    }
    return -1; // nobody is in that position of the mapCell

}



