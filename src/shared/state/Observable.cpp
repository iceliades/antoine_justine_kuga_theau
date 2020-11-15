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
void const Observable::notifyObservers (const StateEvent& e, State& state){
    for (auto observer: observers){
        observer->stateChanged(e,state);
    }
}
