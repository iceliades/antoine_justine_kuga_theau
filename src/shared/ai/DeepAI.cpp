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
    Node best(this->CurrState);

    for (int i = 0; i < root.getChildren().size(); i++)
    {
        int moveval = max_r_minimax(root.getChildren()[i],depth);
        
        if (moveval > bestval)
        {
            bestval = moveval;
            //best = root.getChildren()[i];
        }
    }

    return best;
}

*/

std::list<state::SpaceMapTiles> DeepAI::FindPath (state::SpaceMapTiles& src, state::SpaceMapTiles& target)
{
    std::list<state::SpaceMapTiles> explored;
    queue<std::list<state::SpaceMapTiles>> paths;
    std::list<state::SpaceMapTiles> first;

    first.push_back(src);
    paths.push(first);
    
    // BFS
    while (paths.size() > 0)
    {
        std::list<state::SpaceMapTiles> currPath = paths.front();
        paths.pop();

        bool done = false;
        state::SpaceMapTiles currCell = currPath.back();

        // Checking if node is already done
        for (auto& cell : explored) if (cell.getPosition().equals(currCell.getPosition())) done = true;

        if (!done )//&& currCell.isSpace())
        {
            // FInding available cells to continue path
            std::vector<SpaceMapTiles> nears = findSpaceNeighbours(currCell, currState,target);

            for (auto& near : nears)
            {
                // check if near node already explored
                bool nearDone = false;
                for (auto& visited : explored) if (visited.getPosition().equals(near.getPosition())) nearDone = true;

                // Create new path until reach the target char
                if (!nearDone)
                {
                    list<SpaceMapTiles> new_path(currPath);
                    new_path.push_back(near);
                    paths.push(new_path);
                    if (near.getPosition().equals(target.getPosition())){
                        new_path.pop_front(); // remove the selected char position
                        new_path.pop_back(); // remove the targeted character position
                        return new_path;
                    }
                }
            }
            explored.push_back(currCell);
        }
        
    }
    return first; // no path to target hopefully won't return this
}

vector<SpaceMapTiles> DeepAI::findSpaceNeighbours(SpaceMapTiles& currCell, State& currState,state::SpaceMapTiles& target)
{
    vector<Position> posNearCell = currCell.getPosition().getNearPositions();
    vector<SpaceMapTiles> nears;
    vector<vector<unique_ptr<MapCell>>>& map = currState.getMap();

    for(auto& pos: posNearCell){
        // return target position if nears contain target 
        if(map[pos.getY()][pos.getX()]->getPosition().equals(target.getPosition())){
            SpaceMapTiles mcell2(Sand,pos.getX(),pos.getY(),0);
            nears.push_back(mcell2);
            return nears;
        }
        // return all available nears cells      
        if(map[pos.getY()][pos.getX()]->isSpace() &&
        map[pos.getY()][pos.getX()]->isOccupied(currState)==false ){
            SpaceMapTiles mcell2(Sand,pos.getX(),pos.getY(),0); // tempory
            nears.push_back(mcell2);
        }
    }

    return nears;
}

// pair first: character to select second: target to select
std::pair<int,int> DeepAI::selectCharacter(state::State& curState){

    int minHealth=INT32_MAX;
    int globalminDist=INT32_MAX;
    int minDist= INT32_MAX; // max int
    int tarPlayerID= (this->nbplayers==2)?1:2;
    std::pair<int,int> pIndex;
    bool done=false;
    //std::vector<int> charHealthLowInRange;
    

    // if we have a low health target in range (weapon range + Char movement) we chosse him
    // instead of the character who is at minimal distance
    for(unsigned int i=0; i<curState.getListCharacters(nbplayers-1).size();i++){
        Character& curChar= *curState.getListCharacters(nbplayers-1)[i];
            for (auto& ennemyChar: curState.getListCharacters(tarPlayerID-1)){
                if(curChar.getStatus()!=DEATH &&ennemyChar->getStatus()!=DEATH){
                    // look if there are ennemies in range of char(mov + weapon range)
                    if(curChar.getPosition().distance(ennemyChar->getPosition())<
                    curChar.getMovementLeft()+curChar.getCharWeap()->getMaxRange()){
                        if(ennemyChar->getHealth()<minHealth){
                            minHealth=ennemyChar->getHealth();
                            pIndex.first=i;
                            pIndex.second=ennemyChar->getIndex();
                            done=true;
                        }
                    }
                }
            }
        
    }
    // Choose the character who is at minimal distance from the selected character
    if(!done){
        for(unsigned int i=0; i<curState.getListCharacters(nbplayers-1).size();i++){
        Character& curChar= *curState.getListCharacters(nbplayers-1)[i];
            for (auto& ennemyChar: curState.getListCharacters(tarPlayerID-1)){
                if(curChar.getStatus()!=DEATH &&ennemyChar->getStatus()!=DEATH){
                    if(curChar.getPosition().distance(ennemyChar->getPosition())<minDist){
                        minDist=curChar.getPosition().distance(ennemyChar->getPosition());
                        pIndex.first=i;
                        pIndex.second=ennemyChar->getIndex();
                    }
                }
            }        
        }
    }
    return pIndex;
}

state::MemoryStates DeepAI::getChildren(state::State& currState){

    MemoryStates children;
    std::vector<std::unique_ptr<Character>>& chars = currState.getListCharacters(currState.getCurPlayerID());
    
    
    int targetPlayerID= (currState.getCurPlayerID())==2)? 1:2;
    // A revoir
    std::pair<int,int> charIndex = selectCharacter(currState);

    for (int i = 0; i < chars.size(); i++)
    {
        // ennemy character in range ?
        if(chars[i].allowedAttackTarget(engine.getState()).size() > 0){
            
            // Select The target with the less Health
            Character& targetChar= *engine.getState().getListCharacters(targetPlayerID-1)[charIndex.second];
            unique_ptr<Command> ptr_ac(new Attack_Command(selectedChar,targetChar));
            engine.addCommand(move(ptr_ac)); engine.update();

            if (rand()%2){ // Choose randomly to move or not for now not important
                int mvLeft= selectedChar.getMovementLeft();
                while (mvLeft>0)
                {   
                    Position randPosToMove (selectedChar.getPosition().getNearPositions()[rand()%4]);
                    unique_ptr<Command> ptr_mv ( new Move_Command(selectedChar,randPosToMove));
                    engine.addCommand(move(ptr_mv));engine.update();
                    mvLeft--;

                }
                
            }
    
        }else{

            int mvLeft= selectedChar.getMovementLeft();
            int nextPosInPath=0;

            //Character& targetChar= *engine.getState().getListCharacters(targetPlayerID-1)[charIndex[1]];
            Character& targetChar= *engine.getState().getListCharacters(targetPlayerID-1)[charIndex.second];
            
            // temporary definition fo cells -> nodes for bfs
            SpaceMapTiles src(Sand,selectedChar.getPosition().getX(),selectedChar.getPosition().getY(),0);
            SpaceMapTiles targ(Sand,targetChar.getPosition().getX(),targetChar.getPosition().getY(),0);

            // the best path to target
            list<SpaceMapTiles> pathlist= FindPath(src,targ);
            vector<SpaceMapTiles> path;
            for(auto& node: pathlist){
                path.push_back(node);
            }
            while(mvLeft>0 && nextPosInPath<path.size()){
                
                // move until mvLeft
                SpaceMapTiles cellToGo= path[nextPosInPath];
                Position pos{cellToGo.getPosition().getX(),cellToGo.getPosition().getY()};
                unique_ptr<Command> ptr_mv1 ( new Move_Command(selectedChar,pos));
                engine.addCommand(move(ptr_mv1));engine.update();
                
                // if Allow target in Range attack him
                if(selectedChar.allowedAttackTarget(engine.getState()).size() > 0){
                    
                    Character &targetToAttack = *engine.getState().getListCharacters
                    (targetPlayerID-1)[charIndex.second];
                    unique_ptr<Command> atkCmd(new Attack_Command(selectedChar, targetToAttack));
                    engine.addCommand(move(atkCmd));
                    engine.update();break; // End of turn

                }

                mvLeft--;
                nextPosInPath++;
            }

        }

        unique_ptr<Command> ptr_ft( new Finish_Turn_Command());
        engine.addCommand(move(ptr_ft));engine.update();

        CopyState copy(currState);
        children.add(copy);
    }

    return children;
}

int DeepAI::getValue(state::State& currState){
    std::vector<std::unique_ptr<Character>>& char_p1 = currState.getListCharacters(0)
    std::vector<std::unique_ptr<Character>>& char_p2 = currState.getListCharacters(1)
    int res = 0;

    for (size_t i = 0; i < char_p1.size(); i++) value += char_p1[i]->getHealth();
    for (size_t i = 0; i < char_p2.size(); i++) value -= char_p2[i]->getHealth();

    return res;
}