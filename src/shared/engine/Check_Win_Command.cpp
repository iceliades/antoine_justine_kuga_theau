#include "Check_Win_Command.h"

// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Check_Win_Command::Check_Win_Command()
{
    Id = CHECK_WIN;

}

void Check_Win_Command::exec(state::State &state)
{

    int winnedID;
    unsigned int p1nbDeathChar=0;
    unsigned int p2nbDeathChar=0;
    // Not very optimal code, tired  will see later
    for (auto &charac: state.getListCharacters(0)){ // Player 1
        if(charac->getStatus() == DEATH )
            p1nbDeathChar++;
    }
    for (auto &charac: state.getListCharacters(1)){ // PLayer 2
        if(charac->getStatus() == DEATH )
            p2nbDeathChar++;
    }


    if (p1nbDeathChar==state.getListCharacters(0).size()){
        winnedID=1;
        state.setEndGame(true);
        state.setGameWinner(winnedID);
        StateEvent se{StateEventID::ENDGAME};
        state.notifyObservers(se, state);
        cout << endl << "GAME OVER" << endl;
        cout << endl << "THE GAME WINNER IS THE PLAYER No" << winnedID << endl;
        cout << "\n";
    }
    else if (p2nbDeathChar==state.getListCharacters(1).size()){
        winnedID=2;
        state.setEndGame(true);
        state.setGameWinner(winnedID);
        StateEvent se{StateEventID::ENDGAME};
        state.notifyObservers(se, state);
        cout << endl << "GAME OVER" << endl;
        cout << endl << "THE GAME WINNER IS THE PLAYER No " << winnedID << endl;
        cout << "\n";
    }
    
}