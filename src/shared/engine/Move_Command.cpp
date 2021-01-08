#include "Move_Command.h"

// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Move_Command::Move_Command (state::Character& refTargetedChar, state::Position& refTargetedPos): targetedChar(refTargetedChar), targetedPos(refTargetedPos)
{
    Id = MOVE;
}
Move_Command::~Move_Command() {}


void Move_Command::exec(state::State &state)
{
    cout << "STATE MOVING" << endl;
    bool allowed = false;
    if (targetedChar.getStatus() == SELECTED)
    {
        // if the character has moves to do
        cout << "Move left" << targetedChar.getMovementLeft() << endl;
        if (targetedChar.getMovementLeft() > 0)
        {
            for (auto &pos: targetedChar.allowedMove(state))
            {
                if (pos.equals(targetedPos)){
                    allowed = true;
                    break;
                }
            }
            // Taking effect Immobilised into account
            if (targetedChar.getEffect().getImmobilised())
            {
				allowed = false;
				// Immobilised canceled for next turn
				targetedChar.setEffect(false, false, false);
				cout << "You can't move, you're immobilised." << endl;
			}
            if (allowed)
            {
                // Moving
                targetedChar.getPosition().setX(targetedPos.getX());
                targetedChar.getPosition().setY(targetedPos.getY());
                targetedChar.setMovementLeft(targetedChar.getMovementLeft() - 1);
                // TODO refresh to the base move quantity for each character if the are not death.
                
                cout << "The character " << targetedChar.getName() << " has been moved to (" << targetedPos.getX() << ", " << targetedPos.getY() << ")" << endl;
            }
            else cout << "The character " << targetedChar.getName() << " not allowed to move in that position" << endl;
        }
        else cout <<"NO MOVEMENT LEFT" << endl;
    }
    cout << "\n";
}


// Ajout de la fonction serialize
Json::Value Move_Command::serialize (){
    Json::Value myCommand;
	myCommand["id"] = Id;

    myCommand["player_id"]= targetedChar.getPlayerID();
	myCommand["target_index"] = targetedChar.getIndex();
	myCommand["x"] = targetedPos.getX();
	myCommand["y"] = targetedPos.getY();

	return myCommand;
    
}