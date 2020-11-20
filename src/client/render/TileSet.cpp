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
            resFile="res/textures/map_tileset.png";
            break;
        case CHARTILESET:
            cellWidth=48;
            cellHeight=72;
            resFile="res/textures/characters_tileset.png";
            break;
        default:
            break;
    }

    textureTileSet.loadFromFile(resFile);
}

// Getters

int const TileSet::getCellWidth(){
    return cellWidth;
}

int const TileSet::getCellHeight(){
    return cellHeight;
}

TileSetID TileSet::getTileSetID(){
    return id;
}

sf::Texture& TileSet::getTexture(){
    return textureTileSet;
}
