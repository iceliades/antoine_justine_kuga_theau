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

Sel_Char_Command::~Sel_Char_Command(){};

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


// Ajout de la fonction serialize
Json::Value Sel_Char_Command::serialize (){
    Json::Value myCommand;
	myCommand["id"] = Id;

	myCommand["player_id"] = targetedChar.getPlayerID();
	

	myCommand["target_index"] = targetedChar.getIndex();


	return myCommand;
    
}