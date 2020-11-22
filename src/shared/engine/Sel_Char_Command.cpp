#include "Sel_Char_Command.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Sel_Char_Command::Sel_Char_Command(state::Character& refTargetedChar) : targetedChar(refTargetedChar)
{
    Id = SELECT_CHAR;
}


void Sel_Char_Command::exec(state::State &state)
{
    for( auto & charac : state.getListCharacters(state.getCurPlayerID()-1)){
        if(charac->getStatus() != DEATH && state.getCurPlayerID() == charac->getPlayerID())
            charac->setStatus(AVAILABLE);
    }
    
    targetedChar.setStatus(SELECTED);
    cout << endl << "THE SELECTED CHARACTER IS "<<targetedChar.getName() << endl;
    cout << "\n";

}