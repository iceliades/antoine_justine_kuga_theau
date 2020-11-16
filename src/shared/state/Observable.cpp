#include "Observable.h"
#include <iostream>

using namespace std;
using namespace state;

Observable::Observable(){
    // Will see later
}
Observable::~Observable(){}

void Observable::registerObserver(Observer* observer){
    observers.push_back(observer);
}
void const Observable::notifyObservers (const StateEvent& stateEvent, State& state){
    for (auto observer: observers){
        observer->stateChanged(stateEvent,state);
    }
}
