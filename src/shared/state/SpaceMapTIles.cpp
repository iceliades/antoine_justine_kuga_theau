#include "SpaceMapTiles.h"
#include <iostream>

using namespace std;
using namespace state;

SpaceMapTiles::SpaceMapTiles(SpaceMapTilesID id, int newX, int newY, int p_tileCode)
{
    typeID=id;
    position.setX(newX);
    position.setY(newY);
    tileCode=p_tileCode;
}
SpaceMapTiles::~SpaceMapTiles(){}

bool SpaceMapTiles::isSpace(){ return true;}

SpaceMapTilesID  SpaceMapTiles::getSpaceMapTilesID(){ return typeID;}
void SpaceMapTiles::setSpaceMapTilesID(SpaceMapTilesID id){
    typeID= id;
}

