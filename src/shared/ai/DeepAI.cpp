#include "DeepAI.h"
#include "state.h"
#include "engine.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <queue>
#include <list>

using namespace std;
using namespace ai;
using namespace state;
using namespace engine;


DeepAI::DeepAI(engine::Engine& engine, int nbPlayers, int depth) :  nbplayers(nbPlayers),myEngine(engine),depth(depth){

    //this->CurrState = myEngine.getState();
}


DeepAI::~DeepAI(){

}



void DeepAI::run(engine::Engine& myEngine){

    CopyState cs{rec_minimax(myEngine.getState(),depth).save()};
    myEngine.getState().load(cs);
    myEngine.update();
}


 int DeepAI::max_r_minimax(state::State& root, int depth){
    if (getValue(root) != 0 || depth==0) return getValue(root);
    int max = 0;
   
    MemoryStates ms= getChildren(root);
    for (size_t i = 0; i < ms.getSize(); i++)
    {
        
        state::CopyState& child =ms.get(i);
        int value = min_r_minimax(child.recover(), depth--);
        if (value > max) max = value;
    }
    return max;
}

int DeepAI::min_r_minimax(state::State& root, int depth){
    if (getValue(root) != 0 || depth==0) return getValue(root);

    int min = 0;

    MemoryStates ms= getChildren(root);
    for (size_t i = 0; i < ms.getSize(); i++)
    {
        state::CopyState& child =ms.get(i);
        int   value = max_r_minimax(child.recover(),depth--);
        if (value < min) min = value;
    }
    return min;
}

state::State& DeepAI::rec_minimax(state::State& root, int depth){
    int bestval = -10000;
    //CopyState best(this->myEngine.getState());
    std::queue<CopyState> myqueue;

    MemoryStates ms = getChildren(root);
    for (int i = 0; i < ms.getSize(); i++)
    {   
        CopyState cs= ms.get(i);
        int moveval = max_r_minimax(cs.recover(),depth);
        
        if (moveval > bestval)
        {
            bestval = moveval;
            if(!myqueue.empty()){
                myqueue.pop();     
            }
            myqueue.push(cs);         
        }
    }
    
    return myqueue.front().recover();
}


std::list<state::SpaceMapTiles> DeepAI::FindPath (state::SpaceMapTiles& src, state::SpaceMapTiles& target,state::State& myState)
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
            std::vector<SpaceMapTiles> nears = findSpaceNeighbours(currCell,myState,target);

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

vector<state::SpaceMapTiles> DeepAI::findSpaceNeighbours(SpaceMapTiles& currCell, state::State& currState,state::SpaceMapTiles& target)
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
    

    CopyState cs (currState.save());
    engine::Engine newEngine;
    newEngine.getState().initPlayers();
    newEngine.getState().initMapCell();
    newEngine.getState().load(cs);
   // myEngine.getState().setMode("children_dai");

    
    MemoryStates children;
    std::vector<std::unique_ptr<Character>>& chars = newEngine.getState().getListCharacters(newEngine.getState().getCurPlayerID()-1);
    
    
    int targetPlayerID= (newEngine.getState().getCurPlayerID()==2)? 1:2;
    // A revoir
    std::pair<int,int> charIndex = selectCharacter(newEngine.getState());

    for (int i = 0; i < chars.size(); i++)
    {
        // ennemy character in range ?
        if(chars[i]->allowedAttackTarget(newEngine.getState()).size() > 0){
            
            // Select The target with the less Health
            Character& targetChar= *newEngine.getState().getListCharacters(targetPlayerID-1)[charIndex.second];
            unique_ptr<Command> ptr_ac(new Attack_Command(*chars[i],targetChar));
            newEngine.addCommand(move(ptr_ac)); newEngine.update();

            if (rand()%2){ // Choose randomly to move or not for now not important
                int mvLeft= chars[i]->getMovementLeft();
                while (mvLeft>0)
                {   
                    Position randPosToMove (chars[i]->getPosition().getNearPositions()[rand()%4]);
                    unique_ptr<Command> ptr_mv ( new Move_Command(*chars[i],randPosToMove));
                    newEngine.addCommand(move(ptr_mv));newEngine.update();
                    mvLeft--;

                }
                
            }
    
        }else{

            int mvLeft= chars[i]->getMovementLeft();
            int nextPosInPath=0;

            //Character& targetChar= *engine.getState().getListCharacters(targetPlayerID-1)[charIndex[1]];
            Character& targetChar= *newEngine.getState().getListCharacters(targetPlayerID-1)[charIndex.second];
            
            // temporary definition fo cells -> nodes for bfs
            SpaceMapTiles src(Sand,chars[i]->getPosition().getX(),chars[i]->getPosition().getY(),0);
            SpaceMapTiles targ(Sand,targetChar.getPosition().getX(),targetChar.getPosition().getY(),0);

            // the best path to target
            list<SpaceMapTiles> pathlist= FindPath(src,targ,newEngine.getState());
            vector<SpaceMapTiles> path;
            for(auto& node: pathlist){
                path.push_back(node);
            }
            while(mvLeft>0 && nextPosInPath<path.size()){
                
                // move until mvLeft
                SpaceMapTiles cellToGo= path[nextPosInPath];
                Position pos{cellToGo.getPosition().getX(),cellToGo.getPosition().getY()};
                unique_ptr<Command> ptr_mv1 ( new Move_Command(*chars[i],pos));
                newEngine.addCommand(move(ptr_mv1));newEngine.update();
                
                // if Allow target in Range attack him
                if(chars[i]->allowedAttackTarget(newEngine.getState()).size() > 0){
                    
                    Character &targetToAttack = *newEngine.getState().getListCharacters
                    (targetPlayerID-1)[charIndex.second];
                    unique_ptr<Command> atkCmd(new Attack_Command(*chars[i], targetToAttack));
                    newEngine.addCommand(move(atkCmd));
                    newEngine.update();break; // End of turn

                }

                mvLeft--;
                nextPosInPath++;
            }

        }

        unique_ptr<Command> ptr_ft( new Finish_Turn_Command());
        newEngine.addCommand(move(ptr_ft));myEngine.update();

        CopyState copy(newEngine.getState().save());
        children.add(copy);
    }
    //myEngine.getState().setMode("deep_ai");

    return children;
}

int DeepAI::getValue(state::State& currState){

    int tarPlayerID= (nbplayers==2)?1:2;
    std::vector<std::unique_ptr<Character>>& charac = currState.getListCharacters(nbplayers-1);
    std::vector<std::unique_ptr<Character>>& ennemy = currState.getListCharacters(tarPlayerID-1);
    int res = 0;
  
    for (size_t i = 0; i < charac.size(); i++) res += charac[i]->getHealth();
    for (size_t i = 0; i < ennemy.size(); i++) res -= ennemy[i]->getHealth();
    
    return res;
}