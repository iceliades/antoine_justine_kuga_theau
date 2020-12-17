#include "MemoryState.h"
#include "state.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace state;
using namespace client;

MemoryState::MemoryState(state::State& myState){
    memory = myState;
}

state::State& MemoryState::chargeState(){
    return memory;
}

