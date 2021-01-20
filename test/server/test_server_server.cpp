//
// Created by Justine on 19/01/2021.
// 
#include <boost/test/unit_test.hpp>
#include "../../src/server/server.h"
#include "../../src/shared/state.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;


namespace server{

    BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }
    
    BOOST_AUTO_TEST_CASE(TestClient)
        {   
//--------------------------------------------------- Player -------------------------------------------------------
            {

                Player joueur1("joueur1",true);

                BOOST_CHECK_EQUAL(joueur1.getName(),"joueur1");

                joueur1.setName("Kasparov");
                BOOST_CHECK_EQUAL(joueur1.getName(),"Kasparov");

                BOOST_CHECK_EQUAL(joueur1.getFree(),true);


                BOOST_CHECK_EQUAL(joueur1.getFree(),true);

                joueur1.setFree(false);
                BOOST_CHECK_EQUAL(joueur1.getFree(),false);



            }
//--------------------------------------------------- Game -------------------------------------------------------
  
            {

                server::Game myGame;
                std::unique_ptr<Player> ptr_j1(new Player("joueur1",true));
                std::unique_ptr<Player> ptr_j2(new Player("joueur2",true));
                std::unique_ptr<Player> ptr_j3(new Player("joueur3",true));
                myGame.addPlayer(move(ptr_j1));
                myGame.addPlayer(move(ptr_j2));
                myGame.addPlayer(move(ptr_j3));

                BOOST_TEST(myGame.getPlayers().size()==3);

                myGame.removePlayer(2);
                BOOST_TEST(myGame.getPlayers().size()==2);

                Player* p = myGame.getIdPlayer(1);
                
                
            }
 
        



        }

}