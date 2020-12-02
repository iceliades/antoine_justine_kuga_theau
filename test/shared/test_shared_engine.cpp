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
        
BOOST_AUTO_TEST_CASE(TestEngineNamespace)
        {
			Character Crook(CROOK, "crook", 10, 10, 1);
			Weapon* hache= new Weapon(AXE);
            Crook.setCharWeap(hache););
            Crook.setDodge(15,15);
            Crook.setEffect(false,false,false);
            Crook.setStatus(CharacterStatusID::SELECTED);
            Crook.setHealth(10,10);
            Crook.setIndex(1);
			Crook.setMovement(5);
			Crook.setMovementBonus(13,13);
			Crook.setPrecision(15,15,15,15);


			Position p{10, 9};
			Crook.setPosition(p);
			Crook.setStats(14,14,14,14,14,14);
			
			Character Crook2(CROOK, "crook", 10, 10, 1);
			Weapon* hache= new Weapon(AXE);
            Crook2.setCharWeap(hache););
            Crook2.setDodge(15,15);
            Crook2.setEffect(false,false,false);
            Crook2.setStatus(CharacterStatusID::SELECTED);
            Crook2.setHealth(10,10);
            Crook2.setIndex(1);
			Crook2.setMovement(5);
			Crook2.setMovementBonus(13,13);
			Crook2.setPrecision(15,15,15,15);

			Position p2{11, 10};
			Position p3{10, 10};
			
			Crook2.setPosition(p3);
			Crook2.setStats(14,14,14,14,14,14);
	 
			Move_Command Crook_move(Crook,p2);
			BOOST_CHECK_EQUAL(Crook.getPosition().equals(p2), true);
			
			Attack_Command Crook_attack(Crook,Crook2);
		}
