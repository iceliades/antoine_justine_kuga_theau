#include "../render.h"
#include <iostream>
#include <fstream>

using namespace render;
using namespace state;
using namespace std;

bool TextureArea::loadTextures(state::State& curState,sf::Texture& textureTileSet, sf::Vector2u tileSize, int width, int height){
    texture= textureTileSet;
    quads.setPrimitiveType(sf::Quads);
    quads.resize(1950*900*4); // Screen display for now
    int vertexArrayIndex=0;

    std::vector<std::vector<std::unique_ptr<MapCell>>> &map= curState.getMap();


       for (unsigned int i = 0; i < map.size(); ++i)
    {
        for (unsigned int j = 0; j < map[0].size(); j++){

            int tileNumber = map[i][j]->getTileCode();

            int tx= tileNumber%(320/ 32);
            int ty= tileNumber/(320/ 32 );
            sf::Vertex* quad = &quads[vertexArrayIndex*4];
            vertexArrayIndex++;
            quad[0].position = sf::Vector2f(j*32, i*32);
            quad[1].position = sf::Vector2f((j+1)*32, i*32);
	        quad[2].position = sf::Vector2f((j+1)*32, (i+1)*32);
	        quad[3].position = sf::Vector2f(j*32, (i+1)*32);
            
            quad[0].texCoords = sf::Vector2f(tx * 32, ty * 32);
			quad[1].texCoords = sf::Vector2f((tx + 1) * 32, ty * 32);
			quad[2].texCoords = sf::Vector2f((tx + 1) * 32, (ty + 1) * 32);
			quad[3].texCoords = sf::Vector2f(tx * 32, (ty + 1) * 32);

        }
    }
    return true;
}

void  TextureArea::draw(sf::RenderTarget& target, sf::RenderStates curState) const {
        // Apply a transformation
        curState.transform *= getTransform();

        // Apply texture of the tileset
        curState.texture = &texture;

        // Draw the table with the vertex
        target.draw(quads, curState);
}