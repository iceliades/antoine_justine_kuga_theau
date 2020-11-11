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
            Element e;
            int x =1;

            e.setTileCode(x);
            e.setName("Name");
            BOOST_CHECK_EQUAL(e.getTileCode(), 1);
            BOOST_CHECK_EQUAL(e.getName(), "Name");
//------------------------------------------------------ Stats ---------------------------------------------------------
// Does the basic constructor do its job ?
            Stats stats;
            BOOST_CHECK_EQUAL(stats.getAgility(),8);
            BOOST_CHECK_EQUAL(stats.getArcane(),8);
            BOOST_CHECK_EQUAL(stats.getCourage(),8);
            BOOST_CHECK_EQUAL(stats.getStamina(),8);
            BOOST_CHECK_EQUAL(stats.getStrength(),8);

//Does the 2nd constructor do its job ?
            Stats stats2(0,0,0,0,0,0);
            BOOST_CHECK_EQUAL(stats2.getAgility(),0);
            BOOST_CHECK_EQUAL(stats2.getArcane(),0);
            BOOST_CHECK_EQUAL(stats2.getCourage(),0);
            BOOST_CHECK_EQUAL(stats2.getStamina(),0);
            BOOST_CHECK_EQUAL(stats2.getStrength(),0);

//Do the getters do their job ?
            int fiveteen = 15;
            stats2.setAgility(fiveteen);
            stats2.setArcane(fiveteen);
            stats2.setCourage(fiveteen);
            stats2.setIntelligence(fiveteen);
            stats2.setStamina(fiveteen);
            stats2.setStrength(fiveteen);

            BOOST_CHECK_EQUAL(stats2.getAgility(),15);
            BOOST_CHECK_EQUAL(stats2.getArcane(),15);
            BOOST_CHECK_EQUAL(stats2.getCourage(),15);
            BOOST_CHECK_EQUAL(stats2.getStamina(),15);
            BOOST_CHECK_EQUAL(stats2.getStrength(),15);

            stats.setStats(fiveteen,fiveteen,fiveteen,fiveteen,fiveteen,fiveteen);
            
            BOOST_CHECK_EQUAL(stats2.getAgility(),15);
            BOOST_CHECK_EQUAL(stats2.getArcane(),15);
            BOOST_CHECK_EQUAL(stats2.getCourage(),15);
            BOOST_CHECK_EQUAL(stats2.getStamina(),15);
            BOOST_CHECK_EQUAL(stats2.getStrength(),15);


        }
}
