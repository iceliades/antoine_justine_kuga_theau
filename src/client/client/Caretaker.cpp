#include "Caretaker.h"
#include "state.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace state;
using namespace client;

Caretaker::Caretaker(){

}

Caretaker::~Caretaker(){

}

void Caretaker::addMemory(MementoState& memento){
    MementoState myState{memento};
    savedMemories.push_back(myState);
}

MementoState& Caretaker::getMemory(int index){
    if (index<savedMemories.size() && index!=-1){
        return savedMemories[index];
    }
    return savedMemories[savedMemories.size()-1];
}