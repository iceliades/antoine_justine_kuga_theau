#include "MemoryStates.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;
MemoryStates::MemoryStates(){
}

void MemoryStates::add(CopyState& copyState){
    CopyState cs{copyState};
    memoryStates.push_back(cs);
}

CopyState& MemoryStates::get(int index){
    return memoryStates[index];
}

unsigned int MemoryStates::getSize(){
    return memoryStates.size();
}