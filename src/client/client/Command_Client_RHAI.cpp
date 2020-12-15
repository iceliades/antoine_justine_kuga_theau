#include "Command_Client_RHAI.h"
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdio>

using namespace client;
using namespace state;
using namespace render;
using namespace engine;
using namespace std;

using namespace client;
using namespace std;


Command_Client_RHAI::Command_Client_RHAI() {
}

Command_Client_RHAI::~Command_Client_RHAI(){
}

void Command_Client_RHAI::execute() {
    std::vector<int> stats(2);
    srand(time(NULL));// Init random generator
    // Random_ai vs Random_ai
    for (int i = 0; i<10; i++)
    {

        Engine myEngine; // No confusion to engine packgage
        myEngine.getState().setMode("random_ai");
        myEngine.getState().initPlayers();
        myEngine.getState().initCharacters();
        myEngine.getState().initMapCell();

        // Init ai
        ai::HeuristicAI heuristicAI(myEngine,1);
        ai::RandomAI randomAi;
        randomAi.setNbplayers(2); // PLayer ID 2


        while (myEngine.getState().getEndGame()==false)
        {
            if(myEngine.getState().getCurPlayerID()==1) heuristicAI.run(myEngine);
            else randomAi.run(myEngine);
        }

        if(myEngine.getState().getEndGame()==true)
        {
            if (myEngine.getState().getGameWinner()==1) stats[0] += 1;
            else stats[1] += 1;
        }
    }
    cout << "Heuristic AI victories : " << stats[0] << endl;
    cout << "Random AI victories : " << stats[1] << endl;
    cout << "Percentage win of Heuristic AI : " << 100*stats[0]/(stats[0]+stats[1]) << endl;
}
