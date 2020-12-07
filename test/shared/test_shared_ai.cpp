//
// Created by Justine on 07/1/2020.
// 



#include <iostream>
#include <boost/test/unit_test.hpp>
#include <vector>
#include "../../src/shared/ai.h"
#include "../../src/shared/state.h"
#include <string>


using namespace ::engine;
using namespace ::std;
using namespace ::state;
using namespace ::ai;

 BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }
        
BOOST_AUTO_TEST_CASE(TestAi)
        {
			
            


            State myState;
            myState.setMode("PlayervsAI");
            myState.initMapCell();
            myState.initPlayers();
            myState.initCharacters();

            RandomAI myAi;

            BOOST_CHECK_EQUAL(myAi.getNbplayers (),2);
            myAi.setNbplayers (1);
            BOOST_CHECK_EQUAL(myAi.getNbplayers (),1);
            myAi.setNbplayers (2);
            
            

            





        }
