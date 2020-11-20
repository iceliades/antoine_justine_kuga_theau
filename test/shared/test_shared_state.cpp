//
// Created by theau on 24/10/2020.
// 
#include <boost/test/unit_test.hpp>
#include <string>
//#include "../../src/shared/state/Element.h"


namespace state{

        BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }

        BOOST_AUTO_TEST_CASE(TestState)
        {   
            //Cursor
            {
                
            }
//--------------------------------------------------- Characters -------------------------------------------------------
            {
// Does the basic constructor do its job ?
                Character Crook(CROOK, "crook", 10, 10, 1);
                BOOST_CHECK_EQUAL(Crook.getTileCode(), 1);
                BOOST_CHECK_EQUAL(Crook.getPosition().getY(), 10);
                BOOST_CHECK_EQUAL(Crook.getPosition().getX(), 10);
                BOOST_CHECK_EQUAL(Crook.getTypeID(), CROOK);
                BOOST_CHECK_EQUAL(Crook.getName(), "crook");
                BOOST_CHECK_EQUAL(Crook.getMovement(), 5);
                //BOOST_CHECK_EQUAL(Crook.getMovementLeft(), 5);
                BOOST_CHECK_EQUAL(Crook.getHealth(),30);
                BOOST_CHECK_EQUAL(Crook.getPrecision(), 0.7);
                BOOST_CHECK_EQUAL(Crook.getDodge(), 0.1);
                BOOST_CHECK_EQUAL(Crook.getStatus(), AVAILABLE);
                //BOOST_CHECK_EQUAL(Crook.getDirection(), DOWN);
                //BOOST_CHECK_EQUAL(Crook.getPlayerID(), 0);
                BOOST_CHECK_EQUAL(Crook.isMapCell(), false);

//Do the setters do their job ?

                //Crook.setCharWeap(Weapon* hache(AXE));
                //BOOST_CHECK_EQUAL(Crook.getCharWeap(),hache);

                Crook.setDodge(15,15);
                BOOST_CHECK_EQUAL(Crook.getDodge(),30/60);

                Crook.setEffect(false,true,false);
                BOOST_CHECK_EQUAL(Crook.getEffect().getStunned(), true);

                Crook.setStatus(CharacterStatusID::SELECTED);
                BOOST_CHECK_NE(Crook.getStatus(), CharacterStatusID::AVAILABLE);

                Crook.setHealth(10,10);
                BOOST_CHECK_EQUAL(Crook.getHealth(),3*10+2*10) ;

                Crook.setIndex(1);
                BOOST_CHECK_EQUAL(Crook.getIndex(),1);

                Crook.setName("newCrook");Crook.setMovement(5);
                BOOST_CHECK_EQUAL(Crook.getName(),"newCrook");BOOST_CHECK_EQUAL(Crook.getMovement(),5);

                Crook.setMovement(6);
                BOOST_CHECK_EQUAL(Crook.getMovement(),6);

                Crook.setMovement(5);
                Crook.setMovementBonus(13,13);
                BOOST_CHECK_EQUAL(Crook.getMovement(),7) ;


                Crook.setPrecision(15,15,15,15);
                BOOST_CHECK_EQUAL(Crook.getPrecision(),1);


                //Position p{10, 10};
                //Crook.setPosition(p);
                //BOOST_CHECK_EQUAL(Crook.getPosition().equals(p), true);



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

            Stats stats2(15,15,15,15,15,15);
            BOOST_CHECK_EQUAL(stats2.getAgility(),15);
            BOOST_CHECK_EQUAL(stats2.getArcane(),15);
            BOOST_CHECK_EQUAL(stats2.getCourage(),15);
            BOOST_CHECK_EQUAL(stats2.getStamina(),15);
            BOOST_CHECK_EQUAL(stats2.getStrength(),15);

                 

//Do the setters do their job ?
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
