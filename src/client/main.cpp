#include <iostream>
#include <unistd.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <render.h>
#include <engine.h>
#include <ai.h>
#include <client.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cstdio>
#include <functional>
#include <boost/function.hpp>

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace client;




int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
    std::map<std::string,ICommand_Client*> MethodMap;

    MethodMap["hello"] = (ICommand_Client*)new Command_Client_Hello();
    MethodMap["render"] = (ICommand_Client*)new Command_Client_Render();
    MethodMap["random_ai"] = (ICommand_Client*)new Command_Client_RAI();
    MethodMap["player_vs_rai"] = (ICommand_Client*)new Command_Client_PAI();
    MethodMap["engine"] = (ICommand_Client*)new Command_Client_Engine();
    MethodMap["autre"] = (ICommand_Client*)new Command_Client_Autre();



    if(argc==2) {
        if(MethodMap.find(argv[1])==MethodMap.end()) {
            MethodMap["autre"]->execute();
        }else {
            MethodMap[string(argv[1])]->execute();
        }
        /*if (string(argv[1]) == "hello")
            cout << "Bonjour le monde!" << endl; 
        else if (string(argv[1]) == "state") {
            cout << "Veillez utiliser les commandes make unittest et make code-coverage depuis le dossier build" << endl;
    
        }else if (string(argv[1]) == "render")
        {
            State state;
            state.setMode("render");
            state.setCurAction(MOVING);
            state.initPlayers();
            state.initCharacters();
            state.initMapCell();
            
            sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
            StateLayer stateLayer (state,window);
            
            
            stateLayer.initTextureArea(state);
            while (window.isOpen()){
                sf::Event event;
                 while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                }
                stateLayer.draw(window);
            
                
            }

        }
        else if (string(argv[1]) == "engine")
        {
            cout << "TEST ENGINE" << endl;
            Engine engine;
            engine.getState().setMode("engine");
            engine.getState().initPlayers();
            engine.getState().initCharacters();
            engine.getState().initMapCell();
            cout<<" INIT DONE"<< endl;
            
            sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
            StateLayer stateLayer (engine.getState(),window);
            stateLayer.initTextureArea(engine.getState());

            StateLayer *ptr_stateLayer = &stateLayer;
            engine.getState().registerObserver(ptr_stateLayer);
            
            bool booting=true;
            bool firstround=true;
            bool secondroun=false;
            bool thirdround=false;
            bool fourround=false;
            bool fiveround=false;
            bool sixround=false;
            int p1X;int p1Y;int p2X;int p2Y;
            int priority;

            // hard code health bc its loong either wise
            engine.getState().getListCharacters(0)[0]->setNewHealth(25);
            engine.getState().getListCharacters(0)[0]->setPrecision(15,15,15,15);// precision to 1
            engine.getState().getListCharacters(0)[0]->setDodge(8,8);// set dodge to 0

            engine.getState().getListCharacters(1)[0]->setNewHealth(25);
            engine.getState().getListCharacters(1)[0]->setPrecision(15,15,15,15);// precision to 1
            engine.getState().getListCharacters(1)[0]->setDodge(8,8);// set dodge to 0
            engine.getState().getListCharacters(1)[0]->getCharWeap()->setTypeCapab(TELEPORT); // Teleport Capacity


            while (window.isOpen()){
                sf::Event event;
                if( booting){
                    stateLayer.draw(window);
                    booting=false;
                }
                while (1){
                    if (firstround)
                    {
                        p1X= engine.getState().getListCharacters(0)[0]->getPosition().getX();
                        p1Y= engine.getState().getListCharacters(0)[0]->getPosition().getY();

                        int priority=0;
                        
                        cout << "[Player 1] Character pos( " << engine.getState().getListCharacters(0)[0]->getPosition().getX()
                        << " " << engine.getState().getListCharacters(0)[0]->getPosition().getY() << endl;
                        
                        unique_ptr<engine::Command> ptr_sc(new engine::Sel_Char_Command(*engine.getState().getListCharacters(0)[0]));
                        engine.addCommand(move(ptr_sc), priority++);
                        //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;


                        engine.getState().setCurAction(MOVING); // hard change the sate cur action
                        Position pos1{p1X, ++p1Y};
                        unique_ptr<engine::Command> ptr_mc1(new engine::Move_Command(*engine.getState().getListCharacters(0)[0], pos1));
                        engine.addCommand(move(ptr_mc1), priority++);
                        cout<< "MOVE FROM pos("<<p1X<<","<<p1Y<<")"<<" TO "<<"("<<p1X<<","<<p1Y+1<<")"<<endl;
                        if (engine.getState().getListCharacters(0)[0]->getMovementLeft()==0){
                            
                            engine.getState().setCurAction(ATTACKING); // Hard set Attacking mode
                            cout<<"STATE IN ATTACING MODE: SHOW ATTACK RANGE"<<endl;
                            unique_ptr<engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                            engine.addCommand(move(ptr_ftc), priority++);
                            cout<<"FINISHING TURN"<<endl;
                            firstround=false;
                            secondroun=true;
                        }
                        engine.update();
                    }
                    if (secondroun){
                        engine.getState().setCurAction(IDLE);
                        //Player 2
                        p2X= engine.getState().getListCharacters(1)[0]->getPosition().getX();
                        p2Y= engine.getState().getListCharacters(1)[0]->getPosition().getY();
                        priority=0;
                        
                        cout << "[Player 2] Character pos( " << engine.getState().getListCharacters(1)[0]->getPosition().getX()
                        << " " << engine.getState().getListCharacters(1)[0]->getPosition().getY() << endl;
                        
                        unique_ptr<engine::Command> ptr_sc(new engine::Sel_Char_Command(*engine.getState().getListCharacters(1)[0]));
                        engine.addCommand(move(ptr_sc), priority++);
                        //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;


                        engine.getState().setCurAction(MOVING); // hard change the sate cur action
                        Position pos1{p2X, --p2Y};
                        unique_ptr<engine::Command> ptr_mc2(new engine::Move_Command(*engine.getState().getListCharacters(1)[0], pos1));
                        engine.addCommand(move(ptr_mc2), priority++);
                        cout<< "MOVE FROM pos("<<p2X<<","<<p2Y<<")"<<" TO "<<"("<<p2X<<","<<p2Y+1<<")"<<endl;
                        if (engine.getState().getListCharacters(1)[0]->getMovementLeft()==0){
                            
                            engine.getState().setCurAction(ATTACKING);// Show the attack range
                            cout<<"STATE IN ATTACING MODE: SHOW ATTACK RANGE"<<endl;
                            unique_ptr<engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                            engine.addCommand(move(ptr_ftc), priority++);
                            cout<<"FINISHING TURN"<<endl;
                            secondroun=false;
                            thirdround=true;
                            
                        }
                        engine.update();


                    }
                    if (thirdround){  
                        engine.getState().setCurAction(IDLE);
                        p1X= engine.getState().getListCharacters(0)[0]->getPosition().getX();
                        p1Y= engine.getState().getListCharacters(0)[0]->getPosition().getY();

                        int priority=0;
                        
                        cout << "[Player 1] Character pos( " << engine.getState().getListCharacters(0)[0]->getPosition().getX()
                        << " " << engine.getState().getListCharacters(0)[0]->getPosition().getY() << endl;
                        
                        unique_ptr<engine::Command> ptr_sc(new engine::Sel_Char_Command(*engine.getState().getListCharacters(0)[0]));
                        engine.addCommand(move(ptr_sc), priority++);
                        //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;


                        engine.getState().setCurAction(MOVING); // hard change the sate cur action
                        Position pos1{p1X, ++p1Y};
                        unique_ptr<engine::Command> ptr_mc1(new engine::Move_Command(*engine.getState().getListCharacters(0)[0], pos1));
                        engine.addCommand(move(ptr_mc1), priority++);
                        cout<< "MOVE FROM pos("<<p1X<<","<<p1Y<<")"<<" TO "<<"("<<p1X<<","<<p1Y+1<<")"<<endl;
                        if (engine.getState().getListCharacters(0)[0]->getMovementLeft()==0){
                            
                            engine.getState().setCurAction(ATTACKING); // Hard set Attacking mode
                            cout<<"STATE IN ATTACING MODE: SHOW ATTACK RANGE"<<endl;
                            unique_ptr<engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                            engine.addCommand(move(ptr_ftc), priority++);
                            cout<<"FINISHING TURN"<<endl;
                            thirdround=false;
                            fourround=true;
                        }
                        engine.update();                                    
                   
                    }

                    if (fourround){  
                        engine.getState().setCurAction(IDLE);
                        //Player 2
                        p2X= engine.getState().getListCharacters(1)[0]->getPosition().getX();
                        p2Y= engine.getState().getListCharacters(1)[0]->getPosition().getY();
                        priority=0;
                        
                        cout << "[Player 2] Character pos( " << engine.getState().getListCharacters(1)[0]->getPosition().getX()
                        << " " << engine.getState().getListCharacters(1)[0]->getPosition().getY() << endl;
                        
                        unique_ptr<engine::Command> ptr_sc(new engine::Sel_Char_Command(*engine.getState().getListCharacters(1)[0]));
                        engine.addCommand(move(ptr_sc), priority++);
                        //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;


                        engine.getState().setCurAction(MOVING); // hard change the sate cur action
                        Position pos1{p2X, --p2Y};
                        unique_ptr<engine::Command> ptr_mc2(new engine::Move_Command(*engine.getState().getListCharacters(1)[0], pos1));
                        engine.addCommand(move(ptr_mc2), priority++);
                        cout<< "MOVE FROM pos("<<p2X<<","<<p2Y<<")"<<" TO "<<"("<<p2X<<","<<p2Y+1<<")"<<endl;
                        if (engine.getState().getListCharacters(1)[0]->getMovementLeft()==3){ // has reach attack range
                            // ==3 because the update isn't done yet
                     
                            engine.getState().setCurAction(ATTACKING);// Show the attack range
                            cout<<"STATE IN ATTACING MODE: SHOW ATTACK RANGE"<<endl;

                            unique_ptr<engine::Command> ptr_ac2(new engine::Attack_Command(*engine.getState().getListCharacters(1)[0], *engine.getState().getListCharacters(0)[0]));
                            engine.addCommand(move(ptr_ac2), priority++);
                            cout<< "ATTACKED";


                            unique_ptr<engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                            engine.addCommand(move(ptr_ftc), priority++);
                            cout<<"FINISHING TURN"<<endl;
                            fourround=false;
                            fiveround= true;
                            
                        }
                        engine.update();                                   
                   
                    }if (fiveround){
                        engine.getState().setCurAction(IDLE);
                        p1X= engine.getState().getListCharacters(0)[0]->getPosition().getX();
                        p1Y= engine.getState().getListCharacters(0)[0]->getPosition().getY();

                        int priority=0;
                        
                        cout << "[Player 1] Character pos( " << engine.getState().getListCharacters(0)[0]->getPosition().getX()
                        << " " << engine.getState().getListCharacters(0)[0]->getPosition().getY() << endl;
                        
                        unique_ptr<engine::Command> ptr_sc(new engine::Sel_Char_Command(*engine.getState().getListCharacters(0)[0]));
                        engine.addCommand(move(ptr_sc), priority++);
                        //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;

                        engine.getState().setCurAction(ATTACKING);// Show the attack range
                        cout<<"STATE IN ATTACING MODE: SHOW ATTACK RANGE"<<endl;
                        unique_ptr<engine::Command> ptr_ac1(new engine::Attack_Command(*engine.getState().getListCharacters(0)[0], *engine.getState().getListCharacters(1)[0]));
                        engine.addCommand(move(ptr_ac1), priority++);
                        cout<< "ATTACKED";

                        unique_ptr<engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                        engine.addCommand(move(ptr_ftc), priority++);
                        cout<<"FINISHING TURN"<<endl;
                        fiveround=false;
                        sixround=true;
                        engine.update(); 
                    }if (sixround){
                        engine.getState().setCurAction(IDLE);
                        //Player 2
                        p2X= engine.getState().getListCharacters(1)[0]->getPosition().getX();
                        p2Y= engine.getState().getListCharacters(1)[0]->getPosition().getY();
                        priority=0;
                        
                        cout << "[Player 2] Character pos( " << engine.getState().getListCharacters(1)[0]->getPosition().getX()
                        << " " << engine.getState().getListCharacters(1)[0]->getPosition().getY() << endl;
                        
                        unique_ptr<engine::Command> ptr_sc(new engine::Sel_Char_Command(*engine.getState().getListCharacters(1)[0]));
                        engine.addCommand(move(ptr_sc), priority++);
                        //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;

                        Position posTeleport{p2X-2,p2Y-2};
                        unique_ptr<engine::Command> ptr_cap(new engine::Capab_Command(*engine.getState().getListCharacters(1)[0],
                        *engine.getState().getListCharacters(0)[0],posTeleport));
                        engine.addCommand(move(ptr_cap), priority++);
                        cout <<"TELEPORTING"<<endl;
                        usleep(1000000);

                        engine.getState().setCurAction(ATTACKING);// Show the attack range
                        cout<<"STATE IN ATTACING MODE: SHOW ATTACK RANGE"<<endl;

                        unique_ptr<engine::Command> ptr_ac2(new engine::Attack_Command(*engine.getState().getListCharacters(1)[0], *engine.getState().getListCharacters(0)[0]));
                        engine.addCommand(move(ptr_ac2), priority++);
                        cout<< "ATTACKED";

                        unique_ptr<engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                        engine.addCommand(move(ptr_ftc), priority++);
                        cout<<"FINISHING TURN"<<endl;
                        sixround=false;
                        engine.update();
                    }
                    
                              
                    window.pollEvent(event);
                    if (event.type == sf::Event::Closed)
                        window.close();
                    
                    
                }
                
            }



            
        }else if(string(argv[1]) == "random_ai"){
            // Random_ai vs Random_ai

            srand(time(NULL));// Init random generator 

            Engine myEngine; // No confusion to engine packgage
            myEngine.getState().setMode("random_ai");
            myEngine.getState().initPlayers();
            myEngine.getState().initCharacters();
            myEngine.getState().initMapCell();
            

            sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
            StateLayer stateLayer (myEngine.getState(),window);
            stateLayer.initTextureArea(myEngine.getState());
        
            StateLayer *ptr_stateLayer = &stateLayer;
            myEngine.getState().registerObserver(ptr_stateLayer);

            bool booting=true;

             // Init ai
            ai::RandomAI randomAi1;
            ai::RandomAI randomAi2;

            randomAi1.setNbplayers(1); // PLayer ID 1
            randomAi2.setNbplayers(2); // PLayer ID 2
            // Init some characters stuffs to be  faster
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
         
            while (window.isOpen()){
                sf::Event event;
                if( booting){
                    stateLayer.draw(window);
                    booting=false;
                }
                if(myEngine.getState().getCurPlayerID()==1){
                    //unique_ptr<Command> ptr_ft(new Finish_Turn_Command());
                    //myEngine.addCommand(move(ptr_ft));myEngine.update();
                    if(myEngine.getState().getEndGame()==false)
                        randomAi1.run(myEngine);
                }else
                {
                    if(myEngine.getState().getEndGame()==false)
                        randomAi2.run(myEngine);
                }
                // at the close event seems not working
                // will see later for use this
                if(myEngine.getState().getEndGame()==true) 
                    window.close();                   
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                }
                
            }


        }else if(string(argv[1]) == "player_vs_rai"){
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
            ai::RandomAI randomAi;
            randomAi.setNbplayers(2); // PLayer ID 1

            // Init some characters stuffs to be  faster
            
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
            }

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
                        randomAi.run(myEngine);

                }
                
            }


        }*/
        
    }
    return 0;
}
