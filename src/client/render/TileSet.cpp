#include <string>
#include "../render.h"

using namespace render;

// Constructor

TileSet::TileSet(TileSetID ID,std::string mode){
    id = ID;
    
    switch(id){
        case MAPTILESET:
            cellWidth=32;
            cellHeight=32;         
            if(mode=="test")
                resFile="../../../res/textures/map_tileset.png";
            else
                resFile="res/textures/map_tileset.png";
            
            break;
        case CHARTILESET:
            cellWidth=48;
            cellHeight=72;
            if(mode=="test")
                resFile="../../../res/textures/characters_tileset.png";
            else 
                resFile="res/textures/characters_tileset.png";
            break;
        case CURSORTILESET:
            cellWidth=32;
            cellHeight=32;          
            if(mode=="test")
                resFile="../../../res/textures/Cursor_tileset.png";
            else
                resFile="res/textures/Cursor_tileset.png";
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
