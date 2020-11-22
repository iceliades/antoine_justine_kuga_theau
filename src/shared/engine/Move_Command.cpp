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
                if (pos.equals(targetedPos))         {
                    allowed = true;
                    break;
                }
            }
            if (allowed)
            {
                // Moving
                targetedChar.getPosition().setX(targetedPos.getX());
                targetedChar.getPosition().setY(targetedPos.getY());
                targetedChar.setMovementLeft(targetedChar.getMovementLeft() - 1);
                // TODO refresh to the base move quantity for each character if the are not death.
                
                cout << "The character " << targetedChar.getName() << " has been moved to (" << targetedPos.getX() << ", " << targetedPos.getY() << ")" << endl;
                cout << "The character has " << targetedChar.getMovementLeft() << "Movement left" << endl;
            }
            else
                cout << "The character " << targetedChar.getName() << " not allowed to move in that position" << endl;
        }
        else
            cout <<"NO MOVEMENT LEFT" << endl;
    }
    cout << "\n";
}
