//
// Created by Justine on 02/12/2020.
// 
#include <boost/test/unit_test.hpp>
#include "../../src/client/render.h"
#include "../../src/shared/state.h"
#include <string>
#include <vector>
#include <iostream>


namespace render{

    BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }
    
    BOOST_AUTO_TEST_CASE(TestRender)
        {   
//--------------------------------------------------- TileSet -------------------------------------------------------
            {
                        // TileSet tile
                TileSet tile1(MAPTILESET);
                TileSet tile2(CHARTILESET);
                TileSet tile3(CURSORTILESET);

                BOOST_CHECK_EQUAL(tile1.getCellWidth(), 32);
                BOOST_CHECK_EQUAL(tile1.getCellHeight(), 32);
                BOOST_CHECK_EQUAL(tile1.getTileSetID(), MAPTILESET);
                sf::Texture &t1 = tile1.getTexture();
                BOOST_CHECK_EQUAL(t1.getSize().x,0);

                BOOST_CHECK_EQUAL(tile2.getCellWidth(), 48);
                BOOST_CHECK_EQUAL(tile2.getCellHeight(), 72);
                BOOST_CHECK_EQUAL(tile2.getTileSetID(), CHARTILESET);

                BOOST_CHECK_EQUAL(tile3.getCellWidth(), 32);
                BOOST_CHECK_EQUAL(tile3.getCellHeight(), 32);
                BOOST_CHECK_EQUAL(tile3.getTileSetID(), CURSORTILESET);
                
            }
            
  //--------------------------------------------------- StateLayer -------------------------------------------------------          
            {
                state::State myState;
                myState.setCurAction(state::MOVING);
                myState.setMode("test"); // one character for each player
                myState.initMapCell();
                myState.initPlayers();
                myState.initCharacters();
                myState.getListCharacters(0)[0]->setStatus(state::SELECTED);
                myState.getListCharacters(1)[0]->setStatus(state::SELECTED);
                sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
                window.setVisible(false);
                StateLayer stateLayer (myState,window,"test");

                stateLayer.initTextureArea(myState);
                myState.setGameWinner(1);
                //stateLayer.displayWinner();
                state::StateEvent se(state::ALLCHANGED);
                state::StateEvent se1(state::CHARCHANGED);
                state::StateEvent se2(state::CURSORCHANGED);
                state::StateEvent se3(state::ENDGAME);
                stateLayer.stateChanged(se,myState);
                stateLayer.stateChanged(se1,myState);
                stateLayer.stateChanged(se2,myState);
                stateLayer.stateChanged(se3,myState);
                stateLayer.draw(window);
                //window.close();


                state::State myState2;
                myState2.setCurAction(state::ATTACKING);
                myState2.setMode("test"); // one character for each player
                myState2.initMapCell();
                myState2.initPlayers();
                myState2.initCharacters();
                myState2.getListCharacters(0)[0]->setStatus(state::SELECTED);
                myState2.getListCharacters(1)[0]->setStatus(state::SELECTED);
                sf::RenderWindow window2(sf::VideoMode(32*26+500,32*24), "Zorglub");
                window2.setVisible(false);
                StateLayer stateLayer2 (myState2,window2,"test");
                stateLayer.initTextureArea(myState2);
                //window2.close();



            }
        



        }
}