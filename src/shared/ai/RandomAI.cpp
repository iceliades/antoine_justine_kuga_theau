#include "RandomAI.h"
#include "engine.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

void RandomAI::run(engine::Engine &engine){
    int randomCharSelected = selectCharacter(engine.getState());
    // always select someone
    Character &selectedChar = *engine.getState().getListCharacters(2)[randomCharSelected];
    unique_ptr<Command> selectCommand(new Sel_Char_Command(selectedChar));
    engine.addCommand(move(selectCommand));

    // can attack?
    if (selectedChar.allowedAttackTarget(engine.getState()).size() > 0)
    {
        // can attack
        cout << "first if can attack ? true " << endl;
        int moves = selectedChar.getMovementLeft();
        while (selectedChar.allowedAttackTarget(engine.getState()).size() > 0)
        {
            int random = selectedChar.allowedAttackTarget(engine.getState())[(rand() %
                (selectedChar.allowedAttackTarget(engine.getState()).size()))];

            Character &targetToAttack = *engine.getState().getListCharacters(2)[random];
            // choose to attack or to move (0 move, 1 attack)
            if ((rand() % 2))
            {
                // attack
                unique_ptr<Command> atkCmd(new Attack_Command(selectedChar, targetToAttack));
                engine.addCommand(move(atkCmd));
                engine.update();

                unique_ptr<Command> finTurnCmd(new Finish_Turn_Command());
                engine.addCommand(move(finTurnCmd));
                engine.update();
                return;
            }
            else
            {
                // move
                int randomMove = (rand() % selectedChar.allowedMove(engine.getState()).size());
                Position &p = selectedChar.allowedMove(engine.getState())[randomMove];
                unique_ptr<Command> mvCmd(new Move_Command(selectedChar, p));
                engine.addCommand(move(mvCmd));
                engine.update();
                moves--;
            }
        }
        unique_ptr<Command> finTurnCmd(new Finish_Turn_Command());
        engine.addCommand(move(finTurnCmd));
        engine.update();
    }
    else
    {
        int moves = selectedChar.getMovementLeft();
        while ( moves > 0)
        {
            // can NOT attack, JUST MOVE.
            int randomMove = (rand() % selectedChar.allowedMove(engine.getState()).size());
            Position p{selectedChar.allowedMove(engine.getState())[randomMove].getX(),
                selectedChar.allowedMove(engine.getState())[randomMove].getY()};

            unique_ptr<Command> mvCmd(new Move_Command(selectedChar, p));
            engine.addCommand(move(mvCmd));
            engine.update();
            moves--;
            cout << " move executed " << endl;

            // now i was deplaced, can attack?
            if (selectedChar.allowedAttackTarget(engine.getState()).size())
            {
                // just attack
                int random = selectedChar.allowedAttackTarget(engine.getState())[(rand()
                    % (selectedChar.allowedAttackTarget(engine.getState()).size()))];

                Character &targetToAttack = *engine.getState().getListCharacters(2)[random];
                unique_ptr<Command> atkCmd(new Attack_Command(selectedChar, targetToAttack));
                engine.addCommand(move(atkCmd));
                engine.update();

                unique_ptr<Command> finTurnCmd(new Finish_Turn_Command());
                engine.addCommand(move(finTurnCmd));
                engine.update();
                return;
            }
        }
        unique_ptr<Command> finTurnCmd(new Finish_Turn_Command());
        engine.addCommand(move(finTurnCmd));
        engine.update();
        return;
    }
}

int RandomAI::selectCharacter (state::State state){
    std::vector<int> posibleIndex;

    for(unsigned int i = 0; i < state.getListCharacters(2).size(); i++){
        Character &charac = *state.getListCharacters(2)[i];
        if(charac.getPlayerID() == this->getNbplayers() && charac.getStatus() != DEATH)
            posibleIndex.push_back(i);
    }

    int randomNumber = rand() % posibleIndex.size();
    cout << "[";
    for(auto &index : posibleIndex){
        cout << index << ", ";
    }
    cout << "]" << endl;
    return posibleIndex[randomNumber];
}
