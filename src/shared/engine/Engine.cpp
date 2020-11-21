#include "engine.h"
#include "Engine.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;
using namespace engine;
using namespace state;
/*
Engine::Engine() : currState("engine")
{
	//record["length"] = 0;
	//record["commands"][0] = "";
}

Engine::Engine(string stateMode) : currState(stateMode)
{
	//record["length"] = 0;
	//record["commands"][0] = "";
}

Engine::~Engine()/µ
{
	
}
/*
bool getRecEn()
{
	return RecEn;
}

void setRecEn(bool enableRecord)
{
	RecEn = enableRecord;
}

Json::Value getRec()
{
	return Rec;
}

State& getState()
{
	State& ref = currState;
	return ref;
}

map<int, unique_ptr<Command>>& getCurrCommands()
{
	return currCommands;
}

void add_PCommands()
{
	int prior = 0;
	unique_ptr<Command> cw(new Check_Win_Command);
	
	if (currCommands.size() > 0) prior = currCommands.rbegin()->first + 1;
	add_Command(move(cw,prior++);
	
}

void add_Command(unique_ptr<Command> ptr_com, int prior = -1)
{
	if (currCommands.size() > 0) prior = currCommands.rbegin()->first + 1;
	else prior = 0;
	
	if (RecEn && ptr_com->getCommandID() != CHECK_WIN)
	{
		Json::Value newCommand = ptr_com->serialize();
		record["Command Array"][record["Size"].asUInt()] = newCommand;
		record["Size"] = record["Size"].asUInt + 1;
	}
	
	currCommands[prior] = move(ptr_com);
}

void update()
{
	if (!currState.getEndGame())
	{
		cout << "Adding passive commands..." << endl;
		add_PCommands();
		cout << "Executing command from player " << currState.getCurPlayer() << endl;
		StateEvent stateEvent(ALLCHANGED);
		bool endTurn = false;
		
		for (size_t i; i < currCommands.size(); i++)
		{
			currCommands[i]->execute(currState);
			currState.notifyObservers(stateEvent, currState);
			if (currState.getMode() == "engine") usleep(200*1000);
		}
		
		map<int, unique_ptr<Command>>::iterator it;
		for (it = currCommands.begin(); it != currCommands.end(); it++) currCommands.erase(it)
	}
	else cout << "Winner found... Game Over" << endl;
}*/
