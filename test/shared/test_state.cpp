//
// Created by theau on 24/10/2020.
//
    #include <boost/test/unit_test.hpp>
#include <string>
#include "../../src/shared/state.h"
#include "../../src/shared/state/Element.h"


namespace state{
    Position::Position() {

    }
    Element::Element() {
        


    };
    Element::~Element() {

    }
    void Element::setTileCode(int x){
        this->tileCode = x;
    };

    int Element::getTileCode(){
        int x = this->tileCode;
        return x;
    };

    void Element::setName(const std::string &name) {
        this->name = name;
    }

    std::string Element::getName(){
        return this->name;
    }


    BOOST_AUTO_TEST_CASE(TestStaticAssert){
        BOOST_CHECK(1);
    };

    BOOST_AUTO_TEST_CASE(TestState){
        Element e;
        int x = 6;
        e.setTileCode(x);
        e.setName("ok");
        BOOST_CHECK_EQUAL(e.getTileCode(),1);


        BOOST_CHECK_EQUAL(e.getTileCode(),x);
        BOOST_CHECK_EQUAL(e.getName(),"ok");
    };

};
