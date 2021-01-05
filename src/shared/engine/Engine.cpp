#include "Engine.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>



using namespace state;
using namespace engine;
using namespace std;

Engine::Engine(){}

Engine::~Engine(){}

state::State& Engine::getState()
{
    return currState;
}

void Engine::addPsvCommands()
{
    int priority = 0;
    // if currentCommands isnt empty
    if (currCommands.size() > 0)
        // find largest priority
        priority = currCommands.rbegin()->first + 1;

    // passive command
    unique_ptr<Command> ptr_cw(new Check_Win_Command());
    addCommand(move(ptr_cw), priority++);
    
}

// add command with priority of excution
void Engine::addCommand(std::unique_ptr<Command> ptr_cmd, int priority)
{
    if (priority == -1)
    {
        // find largest priority
        if (currCommands.size() > 0)
            priority = currCommands.rbegin()->first + 1;
        else
        {
            priority = 0;
        }
    }
    if (enableRecord && ptr_cmd->getId() != CHECK_WIN){
		Json::Value newCommand = ptr_cmd->serialize();
		record["CommandArray"][record["Size"].asUInt()] = newCommand;
		record["Size"] = record["Size"].asUInt() + 1;

	}

    currCommands[priority] = move(ptr_cmd);

}

void Engine::update()
{
    if (!currState.getEndGame())
    {
        cout << "Adding passive commands ..." << endl;
        //if(currState.getMode()!="test")
        addPsvCommands();
        cout << "Executing commands from turn " << currState.getRound() << endl;
        
        StateEvent stateEvent(ALLCHANGED);
        for (size_t i = 0; i < currCommands.size(); i++)
        {
            currCommands[i]->exec(currState);
            currState.notifyObservers(stateEvent, currState);
            if (currState.getMode()=="engine")
			    usleep(200 * 1000); // for the test
        }
        // used iterator erase
        currCommands.erase(currCommands.begin(),currCommands.end());
    }
    else
    {
        cout << "The game is ended, we have a winner" << endl;
    }
}

std::map<int, std::unique_ptr<Command>>& Engine::getCurrCommands (){
    return currCommands;
}

/*void Engine::setState(state::State& newState){
    this->currState=newState;    

}*/

// ******************** Record ***********************//


void Engine::setEnableRecord(bool enableRecord){
    this->enableRecord = enableRecord;
}

bool Engine::getEnableRecord()
{
    return this->enableRecord;
}

Json::Value Engine::getRecord() 
{
	return record;
}






