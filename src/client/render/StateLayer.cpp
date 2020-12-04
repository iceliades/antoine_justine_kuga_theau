#include "../render.h"
#include <iostream>
#include <unistd.h>
#include <cmath>
#include <queue>


using namespace render;
using namespace std;
using namespace state;


StateLayer::StateLayer(state::State& myState, sf::RenderWindow& window,std::string mode):window(window),currentState(myState){
   
    if(mode=="test")
        resPath="../../../res/textures/";
    else
        resPath="res/textures/";
    
    font.loadFromFile(resPath+"arial.ttf");

   //TileSet tileSetMap(MAPTILESET,mode);
   unique_ptr<TileSet>ptr_mapTileset(new TileSet(MAPTILESET,mode));
   
   //screenWidth=myState.getMap()[0].size()*tileSetMap.getCellWidth();
   //screenHeight=myState.getMap().size()*tileSetMap.getCellHeight();

   //TileSet tileSetCharacters(CHARTILESET,mode);
   unique_ptr<TileSet>ptr_charTileset(new TileSet(CHARTILESET,mode));
   

   //TileSet tileSetCursor(CURSORTILESET,mode);
   unique_ptr<TileSet>ptr_cursorTileset(new TileSet(CURSORTILESET,mode));

    
   tileSets.push_back(move(ptr_mapTileset));
   tileSets.push_back(move(ptr_charTileset));
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
    displayText();
    for (auto& m: message)
        window.draw(m);
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
    }else if (stateEvent.stateEventID == StateEventID::ENDGAME)
    {
        displayWinner();
        initTextureArea(state);
        draw(window);
    }
    
}

void StateLayer::displayText (){
 
    sf::VertexArray right_rectangle(sf::Quads, 4);
	right_rectangle[0].position = sf::Vector2f(32*26.f, 0.f);
	right_rectangle[1].position = sf::Vector2f(32*26+500.f, 0.f);
	right_rectangle[2].position = sf::Vector2f(32*26+500.f, 32*24.f);
	right_rectangle[3].position = sf::Vector2f(32*26.f, 32*24.f);
    
    right_rectangle[0].color = sf::Color::White;
    right_rectangle[1].color = sf::Color::White;
    right_rectangle[2].color = sf::Color::Black;
    right_rectangle[3].color = sf::Color::Black;
    window.draw(right_rectangle);

    sf::VertexArray bottom_rectangle(sf::Quads, 4);
	right_rectangle[0].position = sf::Vector2f(0.f, 32*24.f);
	right_rectangle[1].position = sf::Vector2f(32*26.f+500.f, 32*24.f);
	right_rectangle[2].position = sf::Vector2f(32*26.f+500.f, 32*24+100.f);
	right_rectangle[3].position = sf::Vector2f(0.f, 32*24+100.f);
    right_rectangle[0].color = sf::Color::White;
    right_rectangle[1].color = sf::Color::Black;
    right_rectangle[2].color = sf::Color::White;
    right_rectangle[3].color = sf::Color::Black;
    window.draw(bottom_rectangle);

    sf::Text Info;
    Info.setPosition(450.f+10.f,32*24.f+40.f);Info.setFont(font);Info.setFillColor(sf::Color::Red);
    Info.setString("THIS RENDER AND KEYS ONLY FOR NOW UNTIL CLIENT UPDATE AND USE OF CURSOR");Info.setCharacterSize(20);window.draw(Info);

    sf::Text arrow;
    arrow.setPosition(0.f+10.f,32*24.f+10.f);arrow.setFont(font);
    arrow.setString("MOVE: ARROW");arrow.setCharacterSize(20);window.draw(arrow);
    sf::Text att;
    att.setPosition(500.f+10.f,32*24.f+10.f);att.setFont(font);
    att.setString("ATTACK_MODE: A");att.setCharacterSize(20);window.draw(att);

    sf::Text skip;
    skip.setPosition(250.f+10.f,32*24.f+10.f);skip.setFont(font);
    skip.setString("FINISH TURN: S");skip.setCharacterSize(20);window.draw(skip);
    sf::Text tselect;
    tselect.setPosition(0.f+10.f,32*24.f+45.f);tselect.setFont(font);
    tselect.setString("SELECT:  I -> 1   |  O -> 2   |  P-> 3 ");tselect.setCharacterSize(20);window.draw(tselect);
    sf::Text tattack;
    tattack.setPosition(0.f+10.f,32*24.f+70.f);tattack.setFont(font);
    tattack.setString("TARGET:  K -> 1  |  L -> 2  |  M-> 3");tattack.setCharacterSize(20);window.draw(tattack);

    for(unsigned int i=0; i<currentState.getListPlayers().size(); i++){
        for (unsigned int j=0; j<currentState.getListCharacters(i).size();j++){
            if( currentState.getListCharacters(i)[j]->getStatus()!=DEATH){
                state::Character& mychar=*currentState.getListCharacters(i)[j];
                sf::Text textchar;
                textchar.setPosition(32*mychar.getPosition().getX(),32*mychar.getPosition().getY()+10.f);
                textchar.setFont(font);textchar.setCharacterSize(10);textchar.setString(std::to_string(j+1));
                if(currentState.getMode()=="random_ai"){
                    if(i==0){
                        textchar.setFillColor(sf::Color::Blue);
                    }else if(i==1)
                    {
                        textchar.setFillColor(sf::Color::Red);
                     }
                }
                
                
                window.draw(textchar);
            }
            
        }
    }




    sf::Texture logo;
    logo.loadFromFile(resPath+"zorglub.png");
    sf::Sprite spritelogo;
    spritelogo.setPosition(32*26.f+50.f, 0.f);
    spritelogo.setTexture(logo,true);
    window.draw(spritelogo);


    // Player 1 texts
    sf::Text p1;
    p1.setPosition(32*26.f+70.f,300.f);
    p1.setFont(font);
    p1.setString("PLAYER 1");
    p1.setCharacterSize(30);
    if (currentState.getCurPlayerID()==1)
        p1.setFillColor(sf::Color::Green);
    window.draw(p1);
    int indexYPos= p1.getPosition().y + 50.f;
    for(auto& charac :currentState.getListCharacters(0)){
        
        sf::Text textStats1; 
        textStats1.setFont(font);       
        textStats1.setPosition(32*26.f+120.f,indexYPos+15);
        
        std::string str1= charac->getName()+"\n";
        str1+= "HP: "+ std::to_string((charac->getHealth()<=0)? 0: charac->getHealth())+"\n";
        str1+= "Dammage: "+ std::to_string(charac->getCharWeap()->getDammages());
        textStats1.setString(str1);
        if( charac->getStatus()==SELECTED){
            textStats1.setFillColor(sf::Color::Green);
        }
            
        if (charac->getStatus()==DEATH){
            textStats1.setFillColor(sf::Color::Red);
            p1.setFillColor(sf::Color::Red);             
        }         
        textStats1.setCharacterSize(15);
        
        
        sf::Texture logo;
        switch (charac->getTypeID()){
            case (CROOK) :
                 logo.loadFromFile(resPath+"bandit.png");
            break;
            case (KNIGHT) :
                logo.loadFromFile(resPath+"chevalier.png");
            break;
            case (ELF) :
                logo.loadFromFile(resPath+"elfe.png");
            break;
            case (NATIVE) :
                logo.loadFromFile(resPath+"indien.png");
            break;
            case (DWARF) :
                logo.loadFromFile(resPath+"nain.png");
            break;
            case (PIRATE) :
                logo.loadFromFile(resPath+"pirate.png");
            case (TROLL):
                logo.loadFromFile(resPath+"troll.png");
            
            default:
                break;
        }

        sf::Sprite spritelogo;
        spritelogo.setPosition(32*26.f+10.f, indexYPos);
        spritelogo.setTexture(logo,true);
        window.draw(textStats1);
        window.draw(spritelogo);
        indexYPos+=110;
        
    }

    sf::Texture vslogo;
    vslogo.loadFromFile(resPath+"vs.png");
    sf::Sprite vsSprite;
    vsSprite.setPosition(32*26.f+220.f,300.f);
    vsSprite.setTexture(vslogo,true);
    window.draw(vsSprite);


    sf::Text p2;
    p2.setPosition(32*26.f+310.f,300.f);
    p2.setFont(font);
    p2.setString("PLAYER 2");
    p2.setCharacterSize(30);
     if (currentState.getCurPlayerID()==2)
        p2.setFillColor(sf::Color::Green);
    window.draw(p2);

    int indexYPos2= p2.getPosition().y + 50.f;
    for(auto& charac :currentState.getListCharacters(1)){
        
        sf::Text textStats2; 
        textStats2.setFont(font);       
        textStats2.setPosition(32*26.f+280.f,indexYPos2+15);
        
        std::string str2= charac->getName()+"\n";
        str2+= "HP: "+ std::to_string((charac->getHealth()<=0)? 0: charac->getHealth())+"\n";
        str2+= "Dammage: "+ std::to_string(charac->getCharWeap()->getDammages());
        textStats2.setString(str2);
        if( charac->getStatus()==SELECTED){
            textStats2.setFillColor(sf::Color::Green);
            p2.setFillColor(sf::Color::Green);
        }
            
        if (charac->getStatus()==DEATH){
            textStats2.setFillColor(sf::Color::Red);
            p2.setFillColor(sf::Color::Red);             
        }         
        textStats2.setCharacterSize(15);
        

        sf::Texture logo;
        
        switch (charac->getTypeID()){
            case (CROOK) :
                 logo.loadFromFile(resPath+"bandit.png");
            break;
            case (KNIGHT) :
                logo.loadFromFile(resPath+"chevalier.png");
            break;
            case (ELF) :
                logo.loadFromFile(resPath+"elfe.png");
            break;
            case (NATIVE) :
                logo.loadFromFile(resPath+"indien.png");
            break;
            case (DWARF) :
                logo.loadFromFile(resPath+"nain.png");
            break;
            case (PIRATE) :
                logo.loadFromFile(resPath+"pirate.png");
            case (TROLL):
                logo.loadFromFile(resPath+"troll.png");
            
            default:
                break;
        }

        sf::Sprite spritelogo;
        spritelogo.setPosition(32*26.f+390.f, indexYPos2);
        spritelogo.setTexture(logo,true);
        window.draw(textStats2);
        window.draw(spritelogo);
        indexYPos2+=110;
        
    }


}

void StateLayer::displayWinner(){
    if (currentState.getGameWinner() == 1 || currentState.getGameWinner()==2)
    {
        sf::Text win;
        win.setPosition(currentState.getMap().size()*32 / 2.f, currentState.getMap()[0].size()*32/ 2.f);
        win.setFont(font);
        string str = "PLAYER " + to_string(currentState.getGameWinner()) + " WIN";
        win.setString(str);
        win.setCharacterSize(48);
        win.setFillColor(sf::Color::Red);
        message.push_back(move(win));
    } 
}