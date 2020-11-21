#include "Check_Win_Command.h"
#include "state.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Check_Win_Command::Check_Win_Command()
{
    Id = CHECK_WIN;

}

void Check_Win_Command::Exec(state::State &state)
{

    int winnedID;
    int p1nbDeathChar=0;
    int p2nbDeathChar=0;
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
        //state.setGmaeWinner(winner);
        StateEvent se{StateEventID::ENDGAME};
        state.notifyObservers(se, state);
        cout << endl << "ATENTION!!! THE WINNER IS THE PLAYER " << winnedID << endl;
        cout << endl << "All the opponent's characters are dead" << endl;
    }
    if (p2nbDeathChar==state.getListCharacters(1).size()){
        winnedID=2;
        state.setEndGame(true);
        //state.setGmaeWinner(winner);
        StateEvent se{StateEventID::ENDGAME};
        state.notifyObservers(se, state);
        cout << endl << "ATENTION!!! THE WINNER IS THE PLAYER " << winnedID << endl;
        cout << endl << "All the opponent's characters are dead" << endl;
    }
 
}