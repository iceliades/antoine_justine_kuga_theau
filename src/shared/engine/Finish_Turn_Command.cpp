#include "Finish_Turn_Command.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Finish_Turn_Command::Finish_Turn_Command (){
    Id = FINISH_TURN;

}

void Finish_Turn_Command::exec (state::State& state){

    // for the Player who has finished his turn
    for (auto& charac: state.getListCharacters(state.getCurPlayerID()-1)){
		
		if(charac->getCapab()[0] == 3 || charac->getCapab()[0] == 2 || charac->getCapab()[0] == 1)
		{
			charac->setCapab(charac->getCapab()[0] - 1,0);
			cout <<  charac->getCapab()[0] << " turns remaining before " << charac->getName() << " can use his powers." << endl;
		}
		else if (charac->getCapab()[0] == 0) cout << charac->getName() << " can use his powers." << endl;
		else cout << "Erreur compteur" << endl;
		
        if(charac->getStatus() != DEATH){
            charac->setMovementLeft(charac->getMovement());
            charac->setStatus(WAITING);
            charac->setAttacked(false);           
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
     cout << "\n";

}
