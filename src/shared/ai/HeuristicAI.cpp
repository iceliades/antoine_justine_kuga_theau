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


HeuristicAI::HeuristicAI(engine::Engine& myEngine, int nbplayers){
    this->nbplayers = nbplayers;
    this->currState = myEngine.getState();
}




/*void HeuristicAI::run(engine::Engine& engine){


}*/

// std::vector<state::SpaceMapTiles> HeuristicAI::FindPath (state::SpaceMapTiles& src, state::SpaceMapTiles& target)
// {
//     std::vector<state::SpaceMapTiles> explored;
//     queue<std::vector<state::SpaceMapTiles>> paths;
//     std::vector<state::SpaceMapTiles> first;

//     paths.push(first);
//     first.push_back(src);


//     // Checking if start is destination
//     /*if (src.equals(target))
//     {
//         return first;
//     }*/

//     // BFS
//     while (paths.size() > 0)
//     {
//         std::vector<state::SpaceMapTiles> currPath = paths.front();
//         paths.pop();

//         bool done = false;
//         state::SpaceMapTiles currCell = currPath.back();

//         // Checking if node is already done
//         for (auto& cell : explored) if (cell.equals(currCell)) done = true;

//         if (!done && currCell.isSpace())
//         {
//             // FInding available cells to continue path
//             std::vector<SpaceMapTiles> nears = findSpaceNeighbours(currCell, currState);

//             for (auto& near : nears)
//             {
//                 bool nearDone = false;
//                 for (auto& visited : explored) if (visited.equals(near)) nearDone = true;

//                 if (!nearDone)
//                 {
//                     vector<SpaceMapTiles> new_path(currPath);
//                     new_path.push_back(near);
//                     paths.push(new_path);

//                     if (near.equals(target)) return new_path;
//                 }
//             }
//         }
//         explored.push_back(currCell);
//     }
//     return first;
// }

// vector<SpaceMapTiles> HeuristicAI::findSpaceNeighbours(SpaceMapTiles currCell, State& currState)
// {
//     vector<Position> posNearCell = currCell.getPosition().getNearPositions();
//     vector<SpaceMapTiles> nears;
//     vector<vector<unique_ptr<MapCell>>> map = currState.getMap();

//     for (auto& mline : map)
//     {
//         for (auto& mcell : mline) for (auto& pos : posNearCell) 
//             if (pos.equals((*mcell).getPosition()) && (*mcell).isSpace() && (*mcell).isOccupied(currState)==-1) 
//             {
//                 /* On crée à partir d'une MapCell une instance SpaceMapTiles garantie par isSpace
//                     de TypeID 1 parce qu'inutilisé*/
//                 SpaceMapTilesID id = (SpaceMapTilesID) 1;
//                 int x((*mcell).getPosition().getX()), y((*mcell).getPosition().getY()), p(0);
//                 SpaceMapTiles mcell2 = SpaceMapTiles(id, x, y, p);
//                 nears.push_back(move(mcell2));
//             }
//     }

//     return nears;
// }





