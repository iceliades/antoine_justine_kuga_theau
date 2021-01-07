#include "DeepAI.h"
#include "state.h"
#include "engine.h"

using namespace std;
using namespace ai;


/*
DeepAI::DeepAI(engine::Engine& engine, int nbPlayers, int depth) :  PlayerNumber(nbPlayers),CurrState(engine.getState()),depth(depth){

    //this->CurrState = myEngine.getState();
}


DeepAI::~DeepAI(){
    delete &CurrState;
}



void DeepAI::run(engine::Engine& myEngine){

    Node root(this->CurrState);

}


 int DeepAI::max_r_minimax(Node& node, int depth){
    if (node.getValue() != 0) return node.getValue();

    int max = 0;

    for (size_t i = 0; i < node.getChildren().size(); i++)
    {
        Node& child = node.getChildren()[i];
        int value = min_r_minimax(child, depth--);
        if (value > max) max = value;
    }
    return max;
}

int DeepAI::min_r_minimax(Node& node, int depth){
    if (node.getValue() != 0) return node.getValue();

    int min = 0;

    for (size_t i = 0; i < node.getChildren().size(); i++)
    {
        Node& child = node.getChildren()[i];
        int   value = max_r_minimax(child,depth--);
        if (value < min) min = value;
    }
    return min;
}

Node& DeepAI::rec_minimax(Node& root, int depth){
    int bestval = -10000;
    Node best = new Node(this->currState);

    for (int i = 0; i < root.getChildren().size(); i++)
    {
        int moveval = max_r_minimax(&root.getChildren()[i],depth);
        
        if (moveval > bestval)
        {
            bestval = moveval;
            best = root.getChildren()[i];
        }
    }

    return &best;
} 

*/
