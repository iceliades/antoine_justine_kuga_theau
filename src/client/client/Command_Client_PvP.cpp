#include "Command_Client_PvP.h"
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include "client.h"
#include <iostream>

using namespace client;
using namespace engine;
using namespace render;
using namespace state;
using namespace std;


Command_Client_PvP::Command_Client_PvP() {}
Command_Client_PvP::~Command_Client_PvP(){}

void Command_Client_PvP::execute() 
{
    // Player versus player
    srand(time(NULL));// Init random generator 

    Engine myEngine; // No confusion to engine packgage
    myEngine.getState().setMode("PlayervsPlayer");
    myEngine.getState().initPlayers();
    myEngine.getState().initCharacters();
    myEngine.getState().initMapCell();

    sf::RenderWindow window(sf::VideoMode(32*26+500,32*24+200), "Zorglub");
    StateLayer stateLayer (myEngine.getState(),window);
    stateLayer.initTextureArea(myEngine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    myEngine.getState().registerObserver(ptr_stateLayer);

    bool booting=true;

    client::KeyboardListener key{myEngine};
    // for now hard code for keyboard listener

    // For player 1;
    int indexChar1;
    bool alrdyattacked1 = 0;
    std::vector<unique_ptr<Character>>& playerCharList1 = myEngine.getState().getListCharacters(0);

    // For player 2;
    int indexChar2;
    bool alrdyattacked2 = 0;
    std::vector<unique_ptr<Character>>& playerCharList2 = myEngine.getState().getListCharacters(1);

    while (window.isOpen()){
        sf::Event event;

        // Display changes for the init
        if(booting) stateLayer.draw(window); myEngine.update(); booting=false;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();
            else if(event.type == sf::Event::KeyPressed){
                if(myEngine.getState().getEndGame()==false){

                    /*********************PLAYER 1***********************/
                    if(myEngine.getState().getCurPlayerID()==1){
                        //key.InputManager(event);
                        
                        alrdyattacked2 = 0;

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                        {
                            unique_ptr<Command> ptr_s0(new Sel_Char_Command(*playerCharList1[0]));
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.getState().getCursor().setPosition(playerCharList1[0]->getPosition());
                            myEngine.addCommand(move(ptr_s0));myEngine.update();
                            indexChar1=0;
                        }

                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                        {
                            unique_ptr<Command> ptr_s1(new Sel_Char_Command(*playerCharList1[1]));
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.getState().getCursor().setPosition(playerCharList1[1]->getPosition());
                            myEngine.addCommand(move(ptr_s1));myEngine.update();
                            indexChar1=1;
                        }

                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                        {
                            unique_ptr<Command> ptr_s2(new Sel_Char_Command(*playerCharList1[2]));
                            myEngine.getState().getCursor().setPosition(playerCharList1[2]->getPosition());
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.addCommand(move(ptr_s2));myEngine.update();
                            indexChar1=2;
                        }

                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        {
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList1[indexChar1]->getPosition());
                                ptomove.setX(ptomove.getX()-1);
                                unique_ptr<Command> ptr_mvl(new Move_Command(*playerCharList1[indexChar1],ptomove));
                                myEngine.addCommand(move(ptr_mvl));myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList1[indexChar1]->getPosition());
                                ptomove.setY(ptomove.getY()-1);
                                unique_ptr<Command> ptr_mvu(new Move_Command(*playerCharList1[indexChar1],ptomove));
                                myEngine.addCommand(move(ptr_mvu));myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList1[indexChar1]->getPosition());
                                ptomove.setX(ptomove.getX()+1);
                                unique_ptr<Command> ptr_mvr(new Move_Command(*playerCharList1[indexChar1],ptomove));
                                myEngine.addCommand(move(ptr_mvr));myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList1[indexChar1]->getPosition());
                                ptomove.setY(ptomove.getY()+1);
                                unique_ptr<Command> ptr_mvr(new Move_Command(*playerCharList1[indexChar1],ptomove));
                                myEngine.addCommand(move(ptr_mvr));myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(ATTACKING);
                                myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
                            if(myEngine.getState().getCurAction()==ATTACKING && !alrdyattacked1)
                            {
                                unique_ptr<Command> ptr_ac0(new Attack_Command(*playerCharList1[indexChar1],
                                                                               *myEngine.getState().getListCharacters(1)[0]));
                                myEngine.addCommand(move(ptr_ac0));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update(); alrdyattacked1 = 1;
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
                            if(myEngine.getState().getCurAction()==ATTACKING && !alrdyattacked1){
                                unique_ptr<Command> ptr_ac1(new Attack_Command(*playerCharList1[indexChar1],
                                                                               *myEngine.getState().getListCharacters(1)[1]));
                                myEngine.addCommand(move(ptr_ac1));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update(); alrdyattacked1 = 1;
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                            if(myEngine.getState().getCurAction()==ATTACKING && !alrdyattacked1){
                                unique_ptr<Command> ptr_ac2(new Attack_Command(*playerCharList1[indexChar1],
                                                                               *myEngine.getState().getListCharacters(1)[2]));
                                myEngine.addCommand(move(ptr_ac2));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update(); alrdyattacked1 = 1;
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        {
                            unique_ptr<Command> ptr_ft(new Finish_Turn_Command());
                            myEngine.getState().setCurAction(IDLE);
                            myEngine.addCommand(move(ptr_ft));myEngine.update();
                        }
                    }
                    /*********************PLAYER 2**********************/
                    else if(myEngine.getState().getCurPlayerID()==2){

                        alrdyattacked1 = 0;

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                        {
                            unique_ptr<Command> ptr_s0(new Sel_Char_Command(*playerCharList2[0]));
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.getState().getCursor().setPosition(playerCharList2[0]->getPosition());
                            myEngine.addCommand(move(ptr_s0));myEngine.update();
                            indexChar2=0;
                        }

                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                        {
                            unique_ptr<Command> ptr_s1(new Sel_Char_Command(*playerCharList2[1]));
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.getState().getCursor().setPosition(playerCharList2[1]->getPosition());
                            myEngine.addCommand(move(ptr_s1));myEngine.update();
                            indexChar2=1;
                        }

                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                        {
                            unique_ptr<Command> ptr_s2(new Sel_Char_Command(*playerCharList2[2]));
                            myEngine.getState().getCursor().setPosition(playerCharList2[2]->getPosition());
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.addCommand(move(ptr_s2));myEngine.update();
                            indexChar2=2;
                        }

                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        {
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList2[indexChar2]->getPosition());
                                ptomove.setX(ptomove.getX()-1);
                                unique_ptr<Command> ptr_mvl(new Move_Command(*playerCharList2[indexChar2],ptomove));
                                myEngine.addCommand(move(ptr_mvl));myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList2[indexChar2]->getPosition());
                                ptomove.setY(ptomove.getY()-1);
                                unique_ptr<Command> ptr_mvu(new Move_Command(*playerCharList2[indexChar2],ptomove));
                                myEngine.addCommand(move(ptr_mvu));myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList2[indexChar2]->getPosition());
                                ptomove.setX(ptomove.getX()+1);
                                unique_ptr<Command> ptr_mvr(new Move_Command(*playerCharList2[indexChar2],ptomove));
                                myEngine.addCommand(move(ptr_mvr));myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList2[indexChar2]->getPosition());
                                ptomove.setY(ptomove.getY()+1);
                                unique_ptr<Command> ptr_mvr(new Move_Command(*playerCharList2[indexChar2],ptomove));
                                myEngine.addCommand(move(ptr_mvr));myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING)
                            {
                                myEngine.getState().setCurAction(ATTACKING);
                                myEngine.update();
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
                            if(myEngine.getState().getCurAction()==ATTACKING && !alrdyattacked2)
                            {
                                unique_ptr<Command> ptr_ac0(new Attack_Command(*playerCharList2[indexChar2],
                                                                               *myEngine.getState().getListCharacters(0)[0]));
                                myEngine.addCommand(move(ptr_ac0));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update(); alrdyattacked2 = 1;
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
                            if(myEngine.getState().getCurAction()==ATTACKING && !alrdyattacked2){
                                unique_ptr<Command> ptr_ac1(new Attack_Command(*playerCharList2[indexChar2],
                                                                               *myEngine.getState().getListCharacters(0)[1]));
                                myEngine.addCommand(move(ptr_ac1));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update(); alrdyattacked2 = 1;
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                            if(myEngine.getState().getCurAction()==ATTACKING && !alrdyattacked2){
                                unique_ptr<Command> ptr_ac2(new Attack_Command(*playerCharList2[indexChar2],
                                                                               *myEngine.getState().getListCharacters(0)[2]));
                                myEngine.addCommand(move(ptr_ac2));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update(); alrdyattacked2 = 1;
                            }
                        }
                        
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        {
                            unique_ptr<Command> ptr_ft(new Finish_Turn_Command());
                            myEngine.getState().setCurAction(IDLE);
                            myEngine.addCommand(move(ptr_ft)); myEngine.update();
                        }
                    }

                    else cout << "Fatal error : this ID does not exist" << endl;
                }
            }
        }
    }
}