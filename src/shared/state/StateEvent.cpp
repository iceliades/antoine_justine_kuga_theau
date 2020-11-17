#include "StateEvent.h"
#include <iostream>

using namespace state;

StateEvent::StateEvent(StateEventID eventID) : stateEventID(eventID){}

void StateEvent::setStateEvent(StateEventID newID)
{
    stateEventID = newID;
}