/*
 * test_shared_engine.cpp
 * 
 * Copyright 2020 Vincent Ferrier <vincent@vincent-TravelMate-8331>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <boost/test/unit_test.hpp>
#include <vector>
#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"
#include <string>
//#include "../../src/client/render.h"


using namespace ::engine;
//using namespace ::render;
using namespace std;

 BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }
        
BOOST_AUTO_TEST_CASE(TestEngine)
        {
			State myAllowState;
			myAllowState.initPlayers();
			myAllowState.initCharacters();
			myAllowState.initMapCell();
			myAllowState.setMode("engine");
			
			Position p{10, 9};
			
			/*------------------------Engine--------------------------*/


			
	 
		}
