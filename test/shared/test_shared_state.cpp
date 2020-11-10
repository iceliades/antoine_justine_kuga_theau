//
// Created by theau on 24/10/2020.
//
    #include <boost/test/unit_test.hpp>
#include <string>
#include "../../src/shared/state.h"
#include "../../src/shared/state/Element.h"


namespace state{

        BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        };

        BOOST_AUTO_TEST_CASE(TestState)
        {
            Element e;
            int x =1;

            e.setTileCode(x);
            e.setName("Name");
            BOOST_CHECK_EQUAL(e.getTileCode(), 1);
            BOOST_CHECK_EQUAL(e.getName(), "Name");
        };
};
