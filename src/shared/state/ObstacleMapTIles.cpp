#include "ObstacleMapTiles.h"
#include <iostream>

using namespace std;
using namespace state;


ObstacleMapTiles::ObstacleMapTiles (ObstacleMapTilesID id, int newX, int newY, int p_tileCode)
{
    typeID=id;
    position.setX(newX);
    position.setY(newY);
    tileCode=p_tileCode;

}
ObstacleMapTiles::~ObstacleMapTiles(){}

bool ObstacleMapTiles::isSpace(){ return false;}

//getters and setters
ObstacleMapTilesID ObstacleMapTiles::getObstacleMapTilesID() {
    return typeID; }

void ObstacleMapTiles::setObstacleTilesID(ObstacleMapTilesID id){
    typeID= id;
}

ObstacleMapTiles* ObstacleMapTiles::clone(){
    return new ObstacleMapTiles(*this);
}

