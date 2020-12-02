//
// Created by theau on 24/10/2020.
// 
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <string>
#include <vector>
#include <iostream>


namespace state{

        BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }

        BOOST_AUTO_TEST_CASE(TestState)
        {   
//--------------------------------------------------- Cursor -------------------------------------------------------
            {
                
            }
//--------------------------------------------------- Characters -------------------------------------------------------
            {
// Does the basic constructor do its job ?
                Character Crook(CROOK, "crook", 10, 10, 1);
                Character elf(ELF, "crook", 10, 10, 1);
                Character pirate(PIRATE, "crook", 10, 10, 1);
                Character native(NATIVE, "crook", 10, 10, 1);
                Character troll(TROLL, "crook", 10, 10, 1);
                BOOST_CHECK_EQUAL(Crook.getTileCode(), 1);
                BOOST_CHECK_EQUAL(Crook.getPosition().getY(), 10);
                BOOST_CHECK_EQUAL(Crook.getPosition().getX(), 10);
                BOOST_CHECK_EQUAL(Crook.getTypeID(), CROOK);
                BOOST_CHECK_EQUAL(Crook.getName(), "crook");
                BOOST_CHECK_EQUAL(Crook.getMovement(), 5);
                BOOST_CHECK_EQUAL(Crook.getMovementLeft(), 5);
                BOOST_CHECK_EQUAL(Crook.getHealth(),100);
                BOOST_CHECK_EQUAL(Crook.getPrecision(), 0.7f);
                BOOST_CHECK_EQUAL(Crook.getDodge(), 0.1f);
                BOOST_CHECK_EQUAL(Crook.getStatus(), AVAILABLE);
                BOOST_CHECK_EQUAL(Crook.getDirection(), DOWN);
                BOOST_CHECK_EQUAL(Crook.getPlayerID(), 0);
                BOOST_CHECK_EQUAL(Crook.isMapCell(), false);
                Crook.setTypeID(ELF);
                Crook.setMovementLeft(4);
                Crook.setNewHealth(100);
                Crook.setPlayerID(1);
                Crook.setCapab(0,0);
                BOOST_CHECK_EQUAL(Crook.getCapab()[0],0);
                Crook.addCapab(2);
                BOOST_CHECK_EQUAL(Crook.getCapab()[1],2);
                Crook.setCapused(true);
                BOOST_CHECK_EQUAL(Crook.getCapused(),true);

            

//Do the setters do their job ?
                Weapon* hache= new Weapon(AXE);
                Crook.setCharWeap(hache);
                BOOST_CHECK_EQUAL(Crook.getCharWeap(),hache);

                Crook.setDodge(15,15);
                BOOST_CHECK_EQUAL(Crook.getDodge(),0.1f);

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
                Character knigth(KNIGHT, "crook", 10, 10, 1);
                BOOST_CHECK_EQUAL(knigth.getHealth(),100);


                Position p{10, 10};
                Crook.setPosition(p);
                BOOST_CHECK_EQUAL(Crook.getPosition().equals(p), true);


       
                Crook.setEffect(false,true,false);
                BOOST_CHECK_EQUAL(Crook.getEffect().getStunned(),true);

                Crook.setStats(14,14,14,14,14,14);
                BOOST_CHECK_EQUAL(Crook.getStats().getIntelligence(),14);


                Position p2{-12, -32};
                BOOST_CHECK_GT(p.distance(p2), 0); // distance returns a positive int.

                State myAllowState;
                myAllowState.initPlayers();
                myAllowState.initCharacters();
                myAllowState.initMapCell();
                myAllowState.setMode("engine");
                std::vector<Position> allowpos; 
                int px= myAllowState.getListCharacters(0)[0]->getPosition().getX();
                int py= myAllowState.getListCharacters(0)[0]->getPosition().getY();
                Position pos1{px-1,py};Position pos2{px+1,py};Position pos3{px,py+1};Position pos4{px,py-1};
                allowpos.push_back(pos1);allowpos.push_back(pos2);allowpos.push_back(pos3);allowpos.push_back(pos4);

                myAllowState.getListCharacters(0)[0]->setMovementLeft(1);
                std::vector<Position> posallow= myAllowState.getListCharacters(0)[0]->allowedMove(myAllowState);
                BOOST_CHECK_EQUAL(posallow[0].equals(allowpos[0]),true);
                
                myAllowState.getListCharacters(0)[0]->getCharWeap()->setMaxRange(1.f);
                BOOST_CHECK_EQUAL(myAllowState.getListCharacters(0)[0]->allowedAttackPos(myAllowState)[0].equals(allowpos[0]),true);
                
                std::vector<int> targetallow;targetallow.push_back(0);
                std::vector<int> ta= myAllowState.getListCharacters(0)[0]->allowedAttackTarget(myAllowState);
                ta.push_back(0);
                BOOST_CHECK_EQUAL(ta[0],targetallow[0]);
                
            }

       


//------------------------------------------------------ Effect --------------------------------------------------------

 
            {
				// Effect effect
                Character Crook(CROOK, "crook", 10, 10, 1);

                BOOST_CHECK_EQUAL(Crook.getEffect().getImmobilised(), false);
                BOOST_CHECK_EQUAL(Crook.getEffect().getDisarmed(), false);
                BOOST_CHECK_EQUAL(Crook.getEffect().getStunned(), false);
                
                Crook.setEffect(true,false,false);
                BOOST_CHECK_EQUAL(Crook.getEffect().getImmobilised(),true) ;
                Crook.setEffect(false,false,true);
                BOOST_CHECK_EQUAL(Crook.getEffect().getDisarmed(),true) ;
                Crook.setEffect(false,true,false);
                BOOST_CHECK_EQUAL(Crook.getEffect().getStunned(),true); 
				
				
				
				
			}

//------------------------------------------------ ObstacleMapTiles ----------------------------------------------------

        {
// Does the basic constructor work ?
            ObstacleMapTiles omp(ObstacleMapTilesID::Wall,2,2);

// Do setters and getters work ?
            BOOST_CHECK_EQUAL(omp.isSpace(),false);
            BOOST_CHECK_EQUAL(omp.getObstacleMapTilesID(),ObstacleMapTilesID::Wall);

            omp.setObstacleTilesID(ObstacleMapTilesID::Rock);
            BOOST_CHECK_EQUAL(omp.getObstacleMapTilesID(),ObstacleMapTilesID::Rock);

        }
                        
//------------------------------------------------------ Position ------------------------------------------------------


        {
            // Normal constructor
            Position *posv = new Position();


// do getters et setters and setters work ?
            BOOST_CHECK_EQUAL(posv->getX(), 0);
            BOOST_CHECK_EQUAL(posv->getY(), 0);

            posv->setX(2);
            BOOST_CHECK_EQUAL(posv->getX(), 2);
            posv->setY(3);
            BOOST_CHECK_EQUAL(posv->getY(), 3);

// Overloaded constructor
            Position *post = new Position(2, 3);
            BOOST_CHECK_EQUAL(post->equals(*posv), true); // are post and posv at the same position ?
            //BOOST_CHECK_EQUAL(post->equals(*posv),true); // why posv ?

// does the distance method works ?
            BOOST_CHECK_EQUAL(posv->distance(*post), 0);
            post->setX(0);
            post->setY(0);
            BOOST_CHECK_EQUAL(posv->distance(*post), 5);

            post->setX(2);
            post->setY(2);

// Normal case for the nearest positions
            std::vector<Position> vect = post->getNearPositions();
            int northX = vect[2].getX();
            int northY = vect[2].getY();
            int southX = vect[0].getX();
            int southY = vect[0].getY();
            int westX = vect[3].getX();
            int westY = vect[3].getY();
            int eastX = vect[1].getX();
            int eastY = vect[1].getY();

            BOOST_CHECK_EQUAL(northX, 2);
            BOOST_CHECK_EQUAL(northY, 1);

            BOOST_CHECK_EQUAL(southX, 2);
            BOOST_CHECK_EQUAL(southY, 3);

            BOOST_CHECK_EQUAL(westX, 1);
            BOOST_CHECK_EQUAL(westY, 2);

            BOOST_CHECK_EQUAL(eastX, 3);
            BOOST_CHECK_EQUAL(eastY, 2);

        }

//----------------------------------------------- SpaceMapTiles --------------------------------------------------------
        {
// Does the basic constructor work ?
            SpaceMapTilesID smtID(Sand);
            SpaceMapTiles smt(smtID,2,2,2);

// Do setters and getters work ?
            BOOST_CHECK_EQUAL(smt.isSpace(),true);
            BOOST_CHECK_EQUAL(smt.getSpaceMapTilesID(),smtID);

            smt.setSpaceMapTilesID(SpaceMapTilesID::Grass);
            BOOST_CHECK_EQUAL(smt.getSpaceMapTilesID(),SpaceMapTilesID::Grass);

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

//------------------------------------------------------ Weapon --------------------------------------------------------

                {
                    // Weapon SWORD
                    Weapon Sword(SWORD);

                    BOOST_CHECK_EQUAL(Sword.getDammages(), 13);
                    BOOST_CHECK_EQUAL(Sword.getMinRange(), 1.f);
                    BOOST_CHECK_EQUAL(Sword.getMaxRange(), 2.f);

                    Sword.setDammages(10);
                    BOOST_CHECK_EQUAL(Sword.getDammages(),10) ;
                    Sword.setMinRange(3.f);
                    BOOST_CHECK_EQUAL(Sword.getMinRange(),3.f) ;
                    Sword.setMaxRange(5.f);
                    BOOST_CHECK_EQUAL(Sword.getMaxRange(),5.f);

                    // Weapon AXE
                    Weapon Axe(AXE);

                    BOOST_CHECK_EQUAL(Axe.getDammages(), 14);
                    BOOST_CHECK_EQUAL(Axe.getMinRange(), 1.f);
                    BOOST_CHECK_EQUAL(Axe.getMaxRange(), 1.5f);

                    Axe.setDammages(15);
                    BOOST_CHECK_EQUAL(Axe.getDammages(),15) ;
                    Axe.setMinRange(3.f);
                    BOOST_CHECK_EQUAL(Sword.getMinRange(),3.f) ;
                    Axe.setMaxRange(3.5f);
                    BOOST_CHECK_EQUAL(Axe.getMaxRange(),3.5f);

                    // Weapon Spear
                    Weapon Spear(SPEAR);

                    BOOST_CHECK_EQUAL(Spear.getDammages(), 12);
                    BOOST_CHECK_EQUAL(Spear.getMinRange(), 1.f);
                    BOOST_CHECK_EQUAL(Spear.getMaxRange(), 2.5f);

                    Spear.setDammages(15);
                    BOOST_CHECK_EQUAL(Spear.getDammages(),15) ;
                    Spear.setMinRange(3.f);
                    BOOST_CHECK_EQUAL(Spear.getMinRange(),3.f) ;
                    Spear.setMaxRange(3.5f);
                    BOOST_CHECK_EQUAL(Spear.getMaxRange(),3.5f);

                    // Weapon BOW
                    Weapon Bow(BOW);

                    BOOST_CHECK_EQUAL(Bow.getDammages(), 6);
                    BOOST_CHECK_EQUAL(Bow.getMinRange(), 2.f);
                    BOOST_CHECK_EQUAL(Bow.getMaxRange(), 8.f);

                    Bow.setDammages(10);
                    BOOST_CHECK_EQUAL(Bow.getDammages(),10) ;
                    Bow.setMinRange(3.f);
                    BOOST_CHECK_EQUAL(Bow.getMinRange(),3.f) ;
                    Bow.setMaxRange(3.5f);
                    BOOST_CHECK_EQUAL(Bow.getMaxRange(),3.5f);

                    // Weapon CROSSBOW
                    Weapon Crossbow(CROSSBOW);

                    BOOST_CHECK_EQUAL(Crossbow.getDammages(), 7);
                    BOOST_CHECK_EQUAL(Crossbow.getMinRange(), 2.f);
                    BOOST_CHECK_EQUAL(Crossbow.getMaxRange(), 7.f);

                    Crossbow.setDammages(10);
                    BOOST_CHECK_EQUAL(Crossbow.getDammages(),10) ;
                    Crossbow.setMinRange(3.f);
                    BOOST_CHECK_EQUAL(Crossbow.getMinRange(),3.f) ;
                    Crossbow.setMaxRange(5.f);
                    BOOST_CHECK_EQUAL(Crossbow.getMaxRange(),5.f);

                    // Weapon SLING
                    Weapon Sling(SLING);

                    BOOST_CHECK_EQUAL(Sling.getDammages(), 8);
                    BOOST_CHECK_EQUAL(Sling.getMinRange(), 2.f);
                    BOOST_CHECK_EQUAL(Sling.getMaxRange(), 6.5f);

                    Sling.setDammages(10);
                    BOOST_CHECK_EQUAL(Sling.getDammages(),10) ;
                    Sling.setMinRange(3.f);
                    BOOST_CHECK_EQUAL(Sling.getMinRange(),3.f) ;
                    Sling.setMaxRange(5.f);
                    BOOST_CHECK_EQUAL(Sling.getMaxRange(),5.f);


                    // Weapon WAND
                    Weapon Wand(WAND);

                    BOOST_CHECK_EQUAL(Wand.getDammages(), 10);
                    BOOST_CHECK_EQUAL(Wand.getMinRange(), 3.f);
                    BOOST_CHECK_EQUAL(Wand.getMaxRange(), 4.5f);

                    Wand.setDammages(15);
                    BOOST_CHECK_EQUAL(Wand.getDammages(),15) ;
                    Wand.setMinRange(5.f);
                    BOOST_CHECK_EQUAL(Wand.getMinRange(),5.f) ;
                    Wand.setMaxRange(7.f);
                    BOOST_CHECK_EQUAL(Wand.getMaxRange(),7.f);



                    // Weapon STICK
                    Weapon Stick(STICK);

                    BOOST_CHECK_EQUAL(Stick.getDammages(), 11);
                    BOOST_CHECK_EQUAL(Stick.getMinRange(), 3.f);
                    BOOST_CHECK_EQUAL(Stick.getMaxRange(), 4.f);



                    Stick.setDammages(10);
                    BOOST_CHECK_EQUAL(Stick.getDammages(),10) ;
                    Stick.setMinRange(2.f);
                    BOOST_CHECK_EQUAL(Stick.getMinRange(),2.f) ;
                    Stick.setMaxRange(5.f);
                    BOOST_CHECK_EQUAL(Stick.getMaxRange(),5.f);




                    // Weapon STRAP
                    Weapon Strap(STRAP);

                    BOOST_CHECK_EQUAL(Strap.getDammages(), 9);
                    BOOST_CHECK_EQUAL(Strap.getMinRange(), 3.f);
                    BOOST_CHECK_EQUAL(Strap.getMaxRange(), 5.f);

                    Strap.setDammages(10);
                    BOOST_CHECK_EQUAL(Strap.getDammages(),10) ;
                    Strap.setMinRange(6.f);
                    BOOST_CHECK_EQUAL(Strap.getMinRange(),6.f) ;
                    Strap.setMaxRange(8.f);
                    BOOST_CHECK_EQUAL(Strap.getMaxRange(),8.f);
                    Strap.setTypeCapab(TELEPORT);
                    BOOST_CHECK_EQUAL(Strap.getCType(),TELEPORT);
                    Strap.setOwner("Player1");
                    BOOST_CHECK_EQUAL(Strap.getOwner(),"Player1");


                }




            }


        }

