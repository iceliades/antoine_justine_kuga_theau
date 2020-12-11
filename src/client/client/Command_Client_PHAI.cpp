#include "Command_Client_PAI.h"
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include "client.h"

using namespace client;
using namespace engine;
using namespace render;
using namespace state;
using namespace std;


Command_Client_PAI::Command_Client_PAI() {
}
Command_Client_PAI::~Command_Client_PAI(){
}
void Command_Client_PAI::execute() {
    // Player vs Random_AI

    srand(time(NULL));// Init random generator 

    Engine myEngine; // No confusion to engine packgage
    myEngine.getState().setMode("PlayervsAI");
    myEngine.getState().initPlayers();
    myEngine.getState().initCharacters();
    myEngine.getState().initMapCell();


    sf::RenderWindow window(sf::VideoMode(32*26+500,32*24+200), "Zorglub");
    StateLayer stateLayer (myEngine.getState(),window);
    stateLayer.initTextureArea(myEngine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    myEngine.getState().registerObserver(ptr_stateLayer);

    bool booting=true;

    // Init ai
    ai::HeuristicAI heuristicAI(myEngine,2);
    heuristicAI.setNbplayers(2); // PLayer ID 2

    /*// Init some characters stuffs to be  faster
    Position curPos{2,6}; myEngine.getState().getCursor().setPosition(curPos);
    for(int i=0; i<myEngine.getState().getListPlayers().size(); i++){
        for(int j=0;j<myEngine.getState().getListCharacters(i).size(); j++){
            myEngine.getState().getListCharacters(i)[j]->setNewHealth(25);
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
    }*/

    client::KeyboardListener key{myEngine};
    // for now hard code for keyboard listener
    // For player 1;
    int indexChar;
    //int indexTargetChar;
    std::vector<unique_ptr<Character>>& playerCharList= myEngine.getState().getListCharacters(0);


    while (window.isOpen()){
        sf::Event event;
        if( booting){
            stateLayer.draw(window);
            myEngine.update();
            booting=false;
        }

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }else if(event.type == sf::Event::KeyPressed){
                if(myEngine.getState().getEndGame()==false){
                    if(myEngine.getState().getCurPlayerID()==1){
                        //key.InputManager(event);
                        
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                            unique_ptr<Command> ptr_s0(new Sel_Char_Command(*playerCharList[0]));
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.getState().getCursor().setPosition(playerCharList[0]->getPosition());
                            myEngine.addCommand(move(ptr_s0));myEngine.update();
                            indexChar=0;
                        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
                            unique_ptr<Command> ptr_s1(new Sel_Char_Command(*playerCharList[1]));
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.getState().getCursor().setPosition(playerCharList[1]->getPosition());
                            myEngine.addCommand(move(ptr_s1));myEngine.update();
                            indexChar=1;

                        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                            unique_ptr<Command> ptr_s2(new Sel_Char_Command(*playerCharList[2]));
                            myEngine.getState().setCurAction(CHARSELECTED);
                            myEngine.getState().getCursor().setPosition(playerCharList[2]->getPosition());
                            myEngine.addCommand(move(ptr_s2));myEngine.update();
                            indexChar=2;

                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING){

                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList[indexChar]->getPosition());
                                ptomove.setX(ptomove.getX()-1);
                                unique_ptr<Command> ptr_mvl(new Move_Command(*playerCharList[indexChar],ptomove));
                                myEngine.addCommand(move(ptr_mvl));myEngine.update();

                            }
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING){

                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList[indexChar]->getPosition());
                                ptomove.setY(ptomove.getY()-1);
                                unique_ptr<Command> ptr_mvu(new Move_Command(*playerCharList[indexChar],ptomove));
                                myEngine.addCommand(move(ptr_mvu));myEngine.update();

                            }
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING){

                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList[indexChar]->getPosition());
                                ptomove.setX(ptomove.getX()+1);
                                unique_ptr<Command> ptr_mvr(new Move_Command(*playerCharList[indexChar],ptomove));
                                myEngine.addCommand(move(ptr_mvr));myEngine.update();

                            }
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING){

                                myEngine.getState().setCurAction(MOVING);
                                Position ptomove(playerCharList[indexChar]->getPosition());
                                ptomove.setY(ptomove.getY()+1);
                                unique_ptr<Command> ptr_mvr(new Move_Command(*playerCharList[indexChar],ptomove));
                                myEngine.addCommand(move(ptr_mvr));myEngine.update();

                            }
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                            if(myEngine.getState().getCurAction()==CHARSELECTED
                               || myEngine.getState().getCurAction()==MOVING){
                                myEngine.getState().setCurAction(ATTACKING);
                                myEngine.update();

                            }
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
                            if(myEngine.getState().getCurAction()==ATTACKING){
                                unique_ptr<Command> ptr_ac0(new Attack_Command(*playerCharList[indexChar],
                                                                               *myEngine.getState().getListCharacters(1)[0]));
                                myEngine.addCommand(move(ptr_ac0));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update();
                            }
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
                            if(myEngine.getState().getCurAction()==ATTACKING){
                                unique_ptr<Command> ptr_ac1(new Attack_Command(*playerCharList[indexChar],
                                                                               *myEngine.getState().getListCharacters(1)[1]));
                                myEngine.addCommand(move(ptr_ac1));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update();
                            }
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                            if(myEngine.getState().getCurAction()==ATTACKING){
                                unique_ptr<Command> ptr_ac2(new Attack_Command(*playerCharList[indexChar],
                                                                               *myEngine.getState().getListCharacters(1)[2]));
                                myEngine.addCommand(move(ptr_ac2));myEngine.update();
                                myEngine.getState().setCurAction(IDLE);
                                myEngine.update();
                            }
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                            unique_ptr<Command> ptr_ft(new Finish_Turn_Command());
                            myEngine.getState().setCurAction(IDLE);
                            myEngine.addCommand(move(ptr_ft));myEngine.update();

                        }

                    }


                }

            }

            if( myEngine.getState().getCurPlayerID()==2 && myEngine.getState().getEndGame() == false)
                heuristicAI.run(myEngine);

        }

    }
}