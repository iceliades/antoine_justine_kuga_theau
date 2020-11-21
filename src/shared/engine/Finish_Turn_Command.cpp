#include "Finish_Turn_Command.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Finish_Turn_Command::Finish_Turn_Command (){
    Id = FINISH_TURN;

}

void Finish_Turn_Command::Exec (state::State& state){

    // for the Plyaer for has finished his turn
    for (auto& charac: state.getListCharacters(state.getCurPlayerID()-1)){
        if(charac->getStatus() != DEATH){
            charac->setMovementLeft(charac->getMovement());
            charac->setStatus(WAITING);           
        }
    }
    // change the curPlyaerId for the next
    state.setCurPlayerID((state.getCurPlayerID()== 1) ? 2 : 1);

    // changes for the next Player
    bool cursorpositionned= false;
    for(auto& charac: state.getListCharacters(state.getCurPlayerID()-1)){
        if(charac->getStatus() != DEATH){
            charac->setStatus(AVAILABLE);
            if(!cursorpositionned){
                state.getCursor().setPosition(charac->getPosition());
                cursorpositionned=true;
            }       
        }
    }
 
    // Changes to be oper on render
    state.setCurAction(IDLE);
    state.setRound(state.getRound() + 1);
        // Red or Blue Cursor
    if (state.getCurPlayerID()==1)
        state.getCursor().setTileCode(3);
    else
        state.getCursor().setTileCode(1);
    
     cout << endl << "Turn Changed: Current PLAYER ID " <<state.getCurPlayerID()<< endl;
        

}