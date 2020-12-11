#include "HeuristicAI.h"
#include "state.h"
#include "engine.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <queue>
#include <list>


using namespace ai;
using namespace std;
using namespace state;
using namespace engine;



HeuristicAI::HeuristicAI(engine::Engine& engine, int nbplayers) : currState(engine.getState())
{

    this->nbplayers = nbplayers;
}




std::vector<state::SpaceMapTiles> HeuristicAI::FindPath (state::SpaceMapTiles& src, state::SpaceMapTiles& target)
{
    std::vector<state::SpaceMapTiles> explored;
    queue<std::vector<state::SpaceMapTiles>> paths;
    std::vector<state::SpaceMapTiles> first;

    paths.push(first);
    first.push_back(src);


    // Checking if start is destination
    //if (src.equals(target))
    //{
    //    return first;
    //}

    // BFS
    while (paths.size() > 0)
    {
        std::vector<state::SpaceMapTiles> currPath = paths.front();
        paths.pop();

        bool done = false;
        state::SpaceMapTiles currCell = currPath.back();

        // Checking if node is already done
        for (auto& cell : explored) if (cell.equals(currCell)) done = true;

        if (!done && currCell.isSpace())
        {
            // FInding available cells to continue path
            std::vector<SpaceMapTiles> nears = findSpaceNeighbours(currCell, currState);

            for (auto& near : nears)
            {
                bool nearDone = false;
                for (auto& visited : explored) if (visited.equals(near)) nearDone = true;

                if (!nearDone)
                {
                    vector<SpaceMapTiles> new_path(currPath);
                    new_path.push_back(near);
                    paths.push(new_path);

                    if (near.equals(target)) return new_path;
                }
            }
            explored.push_back(currCell);
        }
        
    }
    return first;
}

vector<SpaceMapTiles> HeuristicAI::findSpaceNeighbours(SpaceMapTiles& currCell, State& currState)
{
    vector<Position> posNearCell = currCell.getPosition().getNearPositions();
    vector<SpaceMapTiles> nears;
    vector<vector<unique_ptr<MapCell>>>& map = currState.getMap();

    for(auto& pos: posNearCell){
        if(map[pos.getY()][pos.getX()]->isSpace() &&
        map[pos.getY()][pos.getX()]->isOccupied(currState)==false ){
            SpaceMapTiles mcell2(Sand,pos.getX(),pos.getY(),0);
            nears.push_back(mcell2);
        }
    }

    /*
    for (auto& mline : map)
    {
        for (auto& mcell : mline) for (auto& pos : posNearCell) 
            if (pos.equals(mcell->getPosition()) && mcell->isSpace() && mcell->isOccupied(currState)==false) 
            {
                //On crée à partir d'une MapCell une instance SpaceMapTiles garantie par isSpace
                //    de TypeID 1 parce qu'inutilisé
                SpaceMapTilesID id = (SpaceMapTilesID) 1;
                int x((*mcell).getPosition().getX()), y((*mcell).getPosition().getY()), p(0);
                SpaceMapTiles mcell2 = SpaceMapTiles(id, x, y, p);
                nears.push_back(move(mcell2));
            }
    }*/

    return nears;
}


void HeuristicAI::run(engine::Engine& engine){

    int targetPlayerID= (this->getNbplayers()==2)? 1:2;

    std::vector<int> charIndex = selectCharacter(engine.getState());
    // always select someone

    Character &selectedChar = *engine.getState().getListCharacters(this->getNbplayers()-1)[charIndex[0]];
    unique_ptr<engine::Command> selectCommand(new Sel_Char_Command(selectedChar));
    engine.addCommand(move(selectCommand));engine.update();

    // ennemy character in range ?
    if(selectedChar.allowedAttackTarget(engine.getState()).size() > 0){
        
        // Select The target with the less Health
        Character& targetChar= *engine.getState().getListCharacters(targetPlayerID-1)[charIndex[1]];
        unique_ptr<Command> ptr_ac(new Attack_Command(selectedChar,targetChar));
        engine.addCommand(move(ptr_ac)); engine.update();

        if (rand()%2){ // Choose randomly to move or not for now
            int mvLeft= selectedChar.getMovementLeft();
            while (mvLeft>0)
            {   
                Position randPosToMove (selectedChar.getPosition().getNearPositions()[rand()%4]);
                unique_ptr<Command> ptr_mv ( new Move_Command(selectedChar,randPosToMove));
                engine.addCommand(move(ptr_mv));engine.update();
                mvLeft=selectedChar.getMovementLeft();

            }
            
        }

        unique_ptr<Command> ptr_ft( new Finish_Turn_Command());
        engine.addCommand(move(ptr_ft));engine.update();
        

    }else{

        int mvLeft1= selectedChar.getMovementLeft();
        int nextPosInPath=0;

        Character& targetChar= *engine.getState().getListCharacters(targetPlayerID-1)[charIndex[1]];

        SpaceMapTiles src(Sand,selectedChar.getPosition().getX(),selectedChar.getPosition().getY(),0);
        SpaceMapTiles targ(Sand,targetChar.getPosition().getX(),targetChar.getPosition().getY(),0);

        vector<SpaceMapTiles> path= FindPath(src,targ);

        while(mvLeft1>0 && nextPosInPath<path.size()){
            
            SpaceMapTiles cellToGo= path[nextPosInPath];
            Position pos{cellToGo.getPosition().getX(),cellToGo.getPosition().getY()};
            unique_ptr<Command> ptr_mv1 ( new Move_Command(selectedChar,pos));
            engine.addCommand(move(ptr_mv1));engine.update();
            

            if(selectedChar.allowedAttackTarget(engine.getState()).size() > 0){
                
                Character &targetToAttack = *engine.getState().getListCharacters(targetPlayerID-1)[charIndex[1]];
                unique_ptr<Command> atkCmd(new Attack_Command(selectedChar, targetToAttack));
                engine.addCommand(move(atkCmd));
                engine.update();break;

             }

            mvLeft1=selectedChar.getMovementLeft();
        }
        unique_ptr<Command> ptr_ft1( new Finish_Turn_Command());
        engine.addCommand(move(ptr_ft1));engine.update();

    }

}

std::vector<int> HeuristicAI::selectCharacter(state::State& curState){

    int minHealth=INT32_MAX;
    int minDist= INT32_MAX; // max int
    int tarPlayerID= (nbplayers==2)?1:2;
    std::vector<int> tabIndex;
    bool done=false;
    //std::vector<int> charHealthLowInRange;

    for(unsigned int i=0; i<curState.getListCharacters(nbplayers-1).size();i++){
        Character& curChar= *curState.getListCharacters(nbplayers-1)[i];
            for (auto& ennemyChar: curState.getListCharacters(tarPlayerID-1)){
                if(ennemyChar->getStatus()!=DEATH){
                    // look if there are ennemies in range of char(mov + weapon range)
                    if(curChar.getPosition().distance(ennemyChar->getPosition())<
                    curChar.getMovementLeft()+curChar.getCharWeap()->getMaxRange()){
                        if(ennemyChar->getHealth()<minHealth){
                            minHealth=ennemyChar->getHealth();
                            tabIndex[0]=i;
                            tabIndex[1]=ennemyChar->getIndex();
                            done=true;
                        }
                    }
                }
            }
        
    }
    if(!done){
        for(unsigned int i=0; i<curState.getListCharacters(nbplayers-1).size();i++){
        Character& curChar= *curState.getListCharacters(nbplayers-1)[i];
            for (auto& ennemyChar: curState.getListCharacters(tarPlayerID-1)){
                if(ennemyChar->getStatus()!=DEATH){
                    // look if there are ennemies in range of char(mov + weapon range)
                    if(curChar.getPosition().distance(ennemyChar->getPosition())<minDist){
                        minDist=curChar.getPosition().distance(ennemyChar->getPosition());
                        tabIndex[0]=i;
                        tabIndex[1]=ennemyChar->getIndex();
                    }
                }
            }
        
        }
    }
}






