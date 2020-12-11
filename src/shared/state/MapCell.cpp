#include "MapCell.h"
#include <iostream>
#include "State.h"
using namespace std;
using namespace state;

bool MapCell::isMapCell(){
    return true;
}

bool MapCell::isOccupied (State& state){
    
    
    unsigned int nbPlayers=  state.getListPlayers().size();
    for (unsigned int  j=0; j<nbPlayers; j++){
        for ( unsigned int i=0; i < state.getListCharacters(j).size();i++){
            if (position.equals(state.getListCharacters(j)[i]->getPosition())&& state.getListCharacters(j)[i]->getStatus()!=DEATH ){
                //return i+ (j*state.getListCharacters(j).size()); // PlayerID * Index in ListCharacters
                return true;
            }

        }     
    }
    return false; // nobody is in that position of the mapCell -1

}


bool MapCell::isOccupiedbyAlly(State& state){
    
     
    unsigned int nbPlayers=  state.getListPlayers().size();
    int curPID=state.getCurPlayerID();
   
    for ( unsigned int i=0; i < state.getListCharacters(curPID-1).size();i++){
        if (position.equals(state.getListCharacters(curPID-1)[i]->getPosition())&& state.getListCharacters(curPID-1)[i]->getStatus()!=DEATH ){
            return true ;// an ally is in that position
        }

    }     
    return false;

}


