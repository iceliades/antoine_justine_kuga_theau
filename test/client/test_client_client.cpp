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

                //BOOST_TEST(base == vectNull); // You can't test it just like that bruh
                                                // You either look that they have the same reference
                                                // or test some of their attributes to be the same
                
                state::State myState;
                MemoryState memory(myState);
                care->addMemory(memory);

                vectNull.push_back(myState);
                //BOOST_TEST(base == vectNull); // You can't test it just like that bruh
                                                // You either look that they have the same reference
                                                // or test some of their attributes to be the same

            }
//--------------------------------------------------- MemoryState -------------------------------------------------------
  
            {
                state::State state;
                MemoryState memState(state);

                //BOOST_TEST(state == memState.chargeState()); // You can't test it just like that bruh
                                                               // You either look that they have the same reference
                                                               // or test some of their attributes to be the same

                
            }
 
        



        }

}