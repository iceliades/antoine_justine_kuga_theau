#include "../render.h"
#include <iostream>
#include <unistd.h>
#include <cmath>


using namespace render;
using namespace std;
using namespace state;


StateLayer::StateLayer(state::State& myState, sf::RenderWindow& window):window(window),currentState(myState){
   
    

   TileSet tileSetMap(MAPTILESET);
   unique_ptr<TileSet>ptr_mapTileset(new TileSet(tileSetMap));
   tileSets.push_back(move(ptr_mapTileset));
   //screenWidth=myState.getMap()[0].size()*tileSetMap.getCellWidth();
   //screenHeight=myState.getMap().size()*tileSetMap.getCellHeight();


   TileSet tileSetCharacters(CHARTILESET);
   unique_ptr<TileSet>ptr_charTileset(new TileSet(tileSetCharacters));
   tileSets.push_back(move(ptr_charTileset));

   TileSet tileSetCursor(CURSORTILESET);
   unique_ptr<TileSet>ptr_cursorTileset(new TileSet(CURSORTILESET));
   tileSets.push_back(move(ptr_cursorTileset));
   


}
StateLayer::~StateLayer(){};


void StateLayer::initTextureArea(state::State& myState){
    TextureArea map;
    map.loadTextures(myState,*tileSets[0],myState.getMap()[0].size(),myState.getMap().size());
    unique_ptr<TextureArea> ptr_map(new TextureArea(map));
    
    
    TextureArea Characters;
    Characters.loadCharacters(myState,*tileSets[1],tileSets[0]->getCellWidth(),tileSets[0]->getCellHeight());
    unique_ptr<TextureArea> ptr_char(new TextureArea(Characters));


    TextureArea cursor;
    cursor.loadCursor(myState,*tileSets[2]);
    unique_ptr<TextureArea> ptr_cursor(new TextureArea(cursor));
    
    
    if(textureAreas.size()!=0){
		while(textureAreas.size()!=0){
			textureAreas.pop_back();
		}
	}
    textureAreas.push_back(move(ptr_map));
    textureAreas.push_back(move(ptr_char));
    textureAreas.push_back(move(ptr_cursor));


}

void StateLayer::draw(sf::RenderWindow &window)
{
    window.clear();
    // draw mapcells
    window.draw(*textureAreas[0]);
    window.draw(*textureAreas[1]);
    window.draw(*textureAreas[2]);
    window.display();
}

void StateLayer::stateChanged(const state::StateEvent &stateEvent, state::State &state)
{
    if (stateEvent.stateEventID == StateEventID::ALLCHANGED)
    {
        std::cout << "STATE CHANGED EVENT: all changed" << endl;
        initTextureArea(state);
        draw(window);
    }
      else if (stateEvent.stateEventID == StateEventID::CHARCHANGED)
    {
        initTextureArea(state);
        draw(window);
    }
    else if (stateEvent.stateEventID == StateEventID::CURSORCHANGED)
    {
        initTextureArea(state);
        draw(window);
    }
}