//
// Created by Justine on 02/12/2020.
// 
#include <boost/test/unit_test.hpp>
#include "../../src/client/render.h"
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
        
        // TileSet tile
        TileSet tile1(MAPTILESET);
        TileSet tile2(CHARTILESET);
        TileSet tile3(CURSORTILESET);

        BOOST_CHECK_EQUAL(tile1.getCellWidth(), 32);
        BOOST_CHECK_EQUAL(tile1.getCellHeight(), 32);
        BOOST_CHECK_EQUAL(tile1.getTileSetID(), MAPTILESET);
        BOOST_CHECK_EQUAL(tile1.getTexture(), "res/textures/map_tileset.png");

        BOOST_CHECK_EQUAL(tile2.getCellWidth(), 48);
        BOOST_CHECK_EQUAL(tile2.getCellHeight(), 72);
        BOOST_CHECK_EQUAL(tile2.getTileSetID(), CHARTILESET);
        BOOST_CHECK_EQUAL(tile2.getTexture(), "res/textures/characters_tileset.png");

        BOOST_CHECK_EQUAL(tile3.getCellWidth(), 32);
        BOOST_CHECK_EQUAL(tile3.getCellHeight(), 32);
        BOOST_CHECK_EQUAL(tile3.getTileSetID(), CURSORTILESET);
        BOOST_CHECK_EQUAL(tile3.getTexture(), "res/textures/Cursor_tileset.png");


        }
}