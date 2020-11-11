//
// Created by theau on 24/10/2020.
// 
#include <boost/test/unit_test.hpp>
#include <string>
#include "../../src/shared/state.h"
//#include "../../src/shared/state/Element.h"


namespace state{

        BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }

        BOOST_AUTO_TEST_CASE(TestState)
        {
            {
                Element e;
                int x =1;
                e.setTileCode(x);
                e.setName("Name");
                BOOST_CHECK_EQUAL(e.getTileCode(), 1);
                BOOST_CHECK_EQUAL(e.getName(), "Name");
            }

            {
                // Character
                Character Crook(CROOK, "crook", 10, 10, 1);
                //BOOST_CHECK_EQUAL(Crook.getPosition().getY(), 10);
                //BOOST_CHECK_EQUAL(Crook.getPosition().getX(), 10);
                BOOST_CHECK_EQUAL(Crook.getTypeID(), CROOK);
                BOOST_CHECK_EQUAL(Crook.getName(), "crook");
                BOOST_CHECK_EQUAL(Crook.getMovement(), 5);
                BOOST_CHECK_EQUAL(Crook.getHealth(),100);

                //BOOST_CHECK_EQUAL(Crook.isMapCell(), false);

                Crook.setStatus(CharacterStatusID::SELECTED);
                BOOST_CHECK_NE(Crook.getStatus(), CharacterStatusID::AVAILABLE);

                Crook.setHealth(10,10);
                BOOST_CHECK_EQUAL(Crook.getHealth(),3*10+2*10) ;

                Crook.setMovementBonus(13,13);
                BOOST_CHECK_EQUAL(Crook.getMovement(),7) ;

                Crook.setDodge(15,15);
                BOOST_CHECK_EQUAL(Crook.getDodge(),30/60);
                
                Crook.setPrecision(15,15,15,15);
                BOOST_CHECK_EQUAL(Crook.getPrecision(),1);

                
                //Position p{10, 10};
                //Crook.setPosition(p);
                //BOOST_CHECK_EQUAL(Crook.getPosition().equals(p), true);
                
                
                Crook.setName("newCrook");Crook.setMovement(5);
                BOOST_CHECK_EQUAL(Crook.getName(),"newCrook");BOOST_CHECK_EQUAL(Crook.getMovement(),5);
                
                Character knigth(KNIGHT, "crook", 10, 10, 1);
                BOOST_CHECK_EQUAL(knigth.getHealth(),80);
                //Crook.setEffect(false,true,false);
                //BOOST_CHECK_EQUAL(Crook.getEffect().getStunned(),true);

                //Crook.setStats(14,14,14,14,14,14);
                //BOOST_CHECK_EQUAL(Crook.getStats().getIntelligence(),14);


         
                //Position p2{-12, -32};
                //BOOST_CHECK_GT(p.distance(p2), 0); // distance returns a positive int.

                //Character c2{DISTANCE, true, "Shaker", 10, 10, 1};
                //BOOST_CHECK_EQUAL(c.getPosition().equals(c2.getPosition()), true);

                // inherited equal method from Element
                //Character c1{STRENGHT, true, "Testy", 0, 0, 1};
                //Character c1identical{STRENGHT, true, "Testy", 0, 0, 1};
                //BOOST_CHECK_EQUAL(c1.equals(c1identical), true);




            }

       
//------------------------------------------------------ Stats ---------------------------------------------------------
// Does the basic constructor do its job ?
            {
            Stats stats;
            BOOST_CHECK_EQUAL(stats.getAgility(),8);
            BOOST_CHECK_EQUAL(stats.getArcane(),8);
            BOOST_CHECK_EQUAL(stats.getCourage(),8);
            BOOST_CHECK_EQUAL(stats.getStamina(),8);
            BOOST_CHECK_EQUAL(stats.getStrength(),8);



//Do the getters do their job ?
            int fiveteen = 15;
            stats.setAgility(fiveteen);
            stats.setArcane(fiveteen);
            stats.setCourage(fiveteen);
            stats.setIntelligence(fiveteen);
            stats.setStamina(fiveteen);
            stats.setStrength(fiveteen);

            BOOST_CHECK_EQUAL(stats.getAgility(),15);
            BOOST_CHECK_EQUAL(stats.getArcane(),15);
            BOOST_CHECK_EQUAL(stats.getCourage(),15);
            BOOST_CHECK_EQUAL(stats.getStamina(),15);
            BOOST_CHECK_EQUAL(stats.getStrength(),15);

          
            }



        }
}
