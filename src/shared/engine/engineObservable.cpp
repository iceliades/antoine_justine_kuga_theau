#include "engineObservable.h"
#include "state.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;

//mutable std::vector<Observer*> observers;
engineObservable::engineObservable(){}
engineObservable::~engineObservable(){}


void engineObservable::registerObserver(engineObserver* obs){
	observers.push_back(obs);
}

// For client network 
void engineObservable::notifyUpdate(){
	for(auto observer : observers){
		observer->engineUpdating();
	}
}

void engineObservable::notifyUpdated(){
	for(auto observer : observers){
		observer->engineUpdated();
	}
}
