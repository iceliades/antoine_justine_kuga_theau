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
			
			// Init
			Engine engine;
            engine.getState().setMode("test");
            engine.getState().initPlayers();
            engine.getState().initCharacters();
            engine.getState().initMapCell();
			int p1x=2,p1y=2;
			int p2x=2,p2y=4;
			state::Position newpos1{p1x,p1y};
			state::Position newpos2{p2x,p2y};
			engine.getState().getListCharacters(0)[0]->setPosition(newpos1);
			engine.getState().getListCharacters(1)[0]->setPosition(newpos2);
			engine.getState().getListCharacters(0)[0]->setPrecision(15,15,15,15);// precision to 1
            engine.getState().getListCharacters(0)[0]->setDodge(8,8);// set dodge to 0
            engine.getState().getListCharacters(0)[0]->getCharWeap()->setTypeCapab(state::TELEPORT);

			std::map<int, std::unique_ptr<Command>>& curcmd =engine.getCurrCommands();
			BOOST_CHECK_EQUAL(curcmd.size(),0);
			// Player 1
				//select
			Sel_Char_Command scc(*engine.getState().getListCharacters(0)[0]);
			scc.setID(SELECT_CHAR);BOOST_CHECK_EQUAL(scc.getId(),SELECT_CHAR);
			unique_ptr<Command> ptr_sc(new Sel_Char_Command(*engine.getState().getListCharacters(0)[0]));
				// move
			state::Position dest{p1x,++p1y};
			unique_ptr<Command> ptr_m(new Move_Command(*engine.getState().getListCharacters(0)[0],dest));
				// attack
			unique_ptr<Command> ptr_ac(new Attack_Command(*engine.getState().getListCharacters(0)[0], *engine.getState().getListCharacters(1)[0]));
				// Teleport
			state::Position telepos{++p1x,++p1y};
			unique_ptr<Command> ptr_cap(new Capab_Command(*engine.getState().getListCharacters(0)[0]
			,*engine.getState().getListCharacters(1)[0],telepos));
		
			engine.addCommand(move(ptr_sc));
			engine.addCommand(move(ptr_m));
			engine.addCommand(move(ptr_ac));
			engine.addCommand(move(ptr_cap));
			
			//engine.addCommand(move(ptr_cw));
			engine.update();

							
				// Attacking 2
			engine.getState().getListCharacters(0)[0]->setPrecision(0,0,0,0);// precision to 1
            engine.getState().getListCharacters(0)[0]->setDodge(4,4);
			unique_ptr<Command> ptr_ac2(new Attack_Command(*engine.getState().getListCharacters(0)[0], *engine.getState().getListCharacters(1)[0]));

			
				//Immobilized
			engine.getState().getListCharacters(0)[0]->getCharWeap()->setTypeCapab(state::IMMOBIL);	
			engine.getState().getListCharacters(0)[0]->setCapab(0,0);
			unique_ptr<Command> ptr_cap_immobil(new Capab_Command(*engine.getState().getListCharacters(0)[0]
			,*engine.getState().getListCharacters(1)[0],telepos));
					
			engine.addCommand(move(ptr_ac2));
			engine.addCommand(move(ptr_cap_immobil));
			engine.update();

				//SRAIN 0
			engine.getState().getListCharacters(0)[0]->setCapab(0,0);
			engine.getState().getListCharacters(0)[0]->getCharWeap()->setTypeCapab(state::SRAIN);
			unique_ptr<Command> ptr_cap_ra0(new Capab_Command(*engine.getState().getListCharacters(0)[0]
			,*engine.getState().getListCharacters(1)[0],telepos));
			engine.addCommand(move(ptr_cap_ra0));
			engine.update();

			


				//SRAIN 1
			engine.getState().getListCharacters(0)[0]->setPrecision(15,15,15,15);// precision to 1
            engine.getState().getListCharacters(0)[0]->setDodge(8,8);// Dodge to 0
			engine.getState().getListCharacters(0)[0]->setCapab(0,0);
			engine.getState().getListCharacters(0)[0]->getCharWeap()->setTypeCapab(state::SRAIN);
			unique_ptr<Command> ptr_cap_ra(new Capab_Command(*engine.getState().getListCharacters(0)[0]
			,*engine.getState().getListCharacters(1)[0],telepos));
						
				// Finish Turn
			unique_ptr<Command> ptr_ftc(new Finish_Turn_Command());
			engine.addCommand(move(ptr_cap_ra));
			engine.addCommand(move(ptr_ftc));

			engine.update();

			engine.getState().getListCharacters(0)[0]->setStatus(state::DEATH);
			engine.getState().getListCharacters(0)[1]->setStatus(state::DEATH);
			engine.getState().getListCharacters(0)[2]->setStatus(state::DEATH);
			engine.update();
			engine.getState().setEndGame(false);
			engine.getState().getListCharacters(0)[0]->setStatus(state::WAITING);
			engine.getState().getListCharacters(0)[1]->setStatus(state::WAITING);
			engine.getState().getListCharacters(0)[2]->setStatus(state::WAITING);
			engine.getState().getListCharacters(1)[0]->setStatus(state::DEATH);
			engine.getState().getListCharacters(1)[1]->setStatus(state::DEATH);
			engine.getState().getListCharacters(1)[2]->setStatus(state::DEATH);
			engine.update();
			// Dummy test
			class helloObserver : engineObserver {
            private:
                std::string client = "idle";
            public:
                void engineUpdating() {
                    client = "state changing";
                }
				void engineUpdated(){
					client = "state changed";
				}

                std::string getNotified() { return client; }
            };
			helloObserver *ho = new helloObserver();
			BOOST_CHECK_EQUAL(ho->getNotified(), "idle");	
			engine.registerObserver((engineObserver*)ho);
			engine.notifyUpdate();
			BOOST_CHECK_EQUAL(ho->getNotified(),"state changing");
			engine.notifyUpdated();
			BOOST_CHECK_EQUAL(ho->getNotified(),"state changed");

		}
