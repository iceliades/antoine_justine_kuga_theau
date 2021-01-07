#include "state.h"
#include "engine.h"
#include "Node.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
using namespace ai;
/*
Node::Node(state::State& currState) : char_p1(currState.getListCharacters(0)), char_p2(currState.getListCharacters(1))
{
    for (size_t i = 0; i < char_p1.size(); i++) value += char_p1[i]->getHealth();
    for (size_t i = 0; i < char_p2.size(); i++) value -= char_p2[i]->getHealth();
} 


int Node::getValue()
{
    return value;
}

vector<Node>& Node::getChildren()
{
    return children;
}

void Node::setValue(int newValue){
    this->value=newValue;
}

void Node::addChild(Node newa)
{
    children.push_back(newa);
}
*/