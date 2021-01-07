#include "Caretaker.h"
#include "state.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace state;
using namespace client;

Caretaker::Caretaker(){
    this->savedMemories = std::vector<MemoryState> {};
}

Caretaker::~Caretaker(){

}

void Caretaker::addMemory(MemoryState& memory){
    MemoryState myState{memory};
    savedMemories.push_back(myState);
}

MemoryState& Caretaker::getMemory(int index){
    if (index<savedMemories.size() && index!=-1){
        return savedMemories[index];
    }
    return savedMemories[savedMemories.size()-1];
}

std::vector<MemoryState>& Caretaker::getSavedMemories(){
    return this->savedMemories;
}