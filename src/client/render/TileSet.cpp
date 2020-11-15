#include <string>
#include "../render.h"

using namespace render;

// Constructor

TileSet::TileSet(TileSetID ID){
    id = ID;
    
    switch(id){
        case MAPTILESET:
            cellWidth=32;
            cellHeight=32;
            //imageFile="rsc/Images/characters_tileset_32.png";
            break;
        case CHARTILESET:
            cellWidth=32;
            cellHeight=32;
            resFile="rsc/Images/cursor_32.png";
            break;
        default:
            break;
    }

    //textureTileSet.loadFromFile(imageFile);
}

// Getters

int const TileSet::getCellWidth(){
    return cellWidth;
}

int const TileSet::getCellHeight(){
    return cellHeight;
}

