//
// Created by Justine on 17/12/2020.
// 
#include <boost/test/unit_test.hpp>
#include "../../src/client/client.h"
#include "../../src/shared/state.h"
#include <string>
#include <vector>
#include <iostream>



namespace client{

    BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }
    
    BOOST_AUTO_TEST_CASE(TestClient)
        {   
//--------------------------------------------------- Caretaker -------------------------------------------------------
            {
                // Caretaker
                
                Caretaker *care;
                std::vector<MemoryState> base = care->getSavedMemories();
                std::vector<MemoryState> vectNull = {};

                BOOST_TEST(base == vectNull);
                
                state::State myState;
                MemoryState memory(myState);
                care->addMemory(memory);

                vectNull.push_back(myState);
                BOOST_TEST(base == vectNull);

            }
//--------------------------------------------------- MemoryState -------------------------------------------------------
  
            {
                state::State state;
                MemoryState memState(state);

                BOOST_TEST(state == memState.chargeState());

                
            }
 
        



        }

}