#include "CopyState.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

CopyState::CopyState(state::State& state) : oldstate(state){
}

state::State& CopyState::recover(){
    return oldstate;
}