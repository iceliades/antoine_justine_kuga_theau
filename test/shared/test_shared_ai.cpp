//
// Created by Justine on 07/1/2020.
// 



#include <iostream>
#include <boost/test/unit_test.hpp>
#include <vector>
#include "../../src/shared/ai.h"
#include "../../src/shared/state.h"
#include <string>
#include <engine/Engine.h>


using namespace engine;
using namespace std;
using namespace state;
using namespace ai;

 BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }
        
BOOST_AUTO_TEST_CASE(TestAi)
        {
//------------------------------------------------- AI.cpp -------------------------------------------------------------
            State myState;
            myState.setMode("PlayervsAI");
            myState.initMapCell();
            myState.initPlayers();
            myState.initCharacters();

            RandomAI myAi;


            BOOST_CHECK_EQUAL(myAi.getNbplayers (),2);
            myAi.setNbplayers(1);
            BOOST_CHECK_EQUAL(myAi.getNbplayers (),1);
            myAi.setNbplayers(2);

            // check if the output belongs in [0,2]
            BOOST_CHECK_LE(myAi.selectCharacter(myState),2);
            BOOST_CHECK_GE(myAi.selectCharacter(myState),0);
        }
//------------------------------------------------- RandomAI.cpp -------------------------------------------------------
BOOST_AUTO_TEST_CASE(TestRandomAI)
        {
            Engine myEngine;
            myEngine.getState().setMode("random_ai");
            myEngine.getState().initPlayers();
            myEngine.getState().initCharacters();
            myEngine.getState().initMapCell();

            // Init ai
            ai::RandomAI randomAi1;
            ai::RandomAI randomAi2;
            randomAi1.setNbplayers(1); // PLayer ID 1
            randomAi2.setNbplayers(2); // PLayer ID 2

            for(int i=0; i<myEngine.getState().getListPlayers().size(); i++){
                for(int j=0;j<myEngine.getState().getListCharacters(i).size(); j++){
                    myEngine.getState().getListCharacters(i)[j]->setNewHealth(50);
                    myEngine.getState().getListCharacters(i)[j]->setPrecision(15,15,15,15);// precision to 1
                    myEngine.getState().getListCharacters(i)[j]->setDodge(8,8);
                    if( i==1){
                        Position pos{2+j,4};
                        myEngine.getState().getListCharacters(i)[j]->setPosition(pos);

                    }else{

                        Position pos1{2+j,6};
                        myEngine.getState().getListCharacters(i)[j]->setPosition(pos1);

                    }

                }
            }

            BOOST_TEST_CHECKPOINT("This is where the fun begins");
            std::vector<Position> Pos_Characters_AI_1(3);
            Pos_Characters_AI_1[0] = myEngine.getState().getListCharacters(randomAi1.getNbplayers()-1)[0]->getPosition();
            Pos_Characters_AI_1[1] = myEngine.getState().getListCharacters(randomAi1.getNbplayers()-1)[1]->getPosition();
            Pos_Characters_AI_1[2] = myEngine.getState().getListCharacters(randomAi1.getNbplayers()-1)[2]->getPosition();


            randomAi1.run(myEngine);

            BOOST_CHECK_EQUAL(Pos_Characters_AI_1[0].equals(myEngine.getState().getListCharacters(randomAi1.getNbplayers())[0]->getPosition()),false);
            BOOST_CHECK_EQUAL(Pos_Characters_AI_1[1].equals(myEngine.getState().getListCharacters(randomAi1.getNbplayers())[1]->getPosition()),false);
            BOOST_CHECK_EQUAL(Pos_Characters_AI_1[2].equals(myEngine.getState().getListCharacters(randomAi1.getNbplayers())[2]->getPosition()),false);
            /*BOOST_CHECK_EQUAL(Characters_AI_1,myEngine.getState().getListCharacters(randomAi1.getNbplayers()));
            BOOST_CHECK_EQUAL(Characters_AI_1[0]->getPosition().equals(myEngine.getState()
                .getListCharacters(randomAi1.getNbplayers())[0]->getPosition()),false);
            BOOST_CHECK_EQUAL(Characters_AI_1[1]->getPosition().equals(myEngine.getState()
                .getListCharacters(randomAi1.getNbplayers())[1]->getPosition()),false);
            BOOST_CHECK_EQUAL(Characters_AI_1[2]->getPosition().equals(myEngine.getState()
                .getListCharacters(randomAi1.getNbplayers())[2]->getPosition()),false);*/




        }
