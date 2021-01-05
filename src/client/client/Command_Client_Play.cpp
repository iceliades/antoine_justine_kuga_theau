#include "Command_Client_Play.h"
#include "state.h"
#include "engine.h"
#include "render.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace client;
using namespace std;
using namespace Json;

Command_Client_Play::Command_Client_Play(){}
Command_Client_Play::~Command_Client_Play(){}

void Command_Client_Play::execute(){
   
    engine::Engine myEngine;    
    myEngine.getState().initPlayers();
    myEngine.getState().initCharacters();
    myEngine.getState().initMapCell();

    sf::RenderWindow window(sf::VideoMode(32*26+500,32*24), "Zorglub");
    render::StateLayer stateLayer (myEngine.getState(),window);
    stateLayer.initTextureArea(myEngine.getState());

    render::StateLayer *ptr_stateLayer = &stateLayer;
    myEngine.getState().registerObserver(ptr_stateLayer);

    state::Position pos;
    std::string replayPath="res/record/replay.txt";
    bool booting=true;
    sf::Event event;

    //Reading Json
    std::ifstream cmdFile(replayPath);
    Json::Reader reader;
    Json::Value cmd;
    if(!reader.parse(cmdFile,cmd)){
        cout << "Failed to parse commands\n"
        << reader.getFormattedErrorMessages();
        return;
    }
    cmdFile.close();
    

    if(window.isOpen()){
        sf::Event event;
        if( booting){
            stateLayer.draw(window);
            booting=false;
        }
        for(unsigned int i=0;i<cmd["CommandArray"].size();i++){
            
            if(cmd["CommandArray"][i]["id"].asUInt()==engine::SELECT_CHAR ) {
                    engine::Sel_Char_Command scc{*myEngine.getState().
                getListCharacters(cmd["CommandArray"][i]["player_id"].asUInt()-1)[cmd["CommandArray"][i]["target_index"].asUInt()]};
                unique_ptr<engine::Command> ptr_select(new engine::Sel_Char_Command(scc));
                myEngine.addCommand(move(ptr_select));
                myEngine.update();
            }                 
            else if(cmd["CommandArray"][i]["id"].asUInt()==engine::MOVE ) {
                pos.setX(cmd["CommandArray"][i]["x"].asUInt());
                pos.setY(cmd["CommandArray"][i]["y"].asUInt());
                engine::Move_Command deplacement(*myEngine.getState().
                getListCharacters(cmd["CommandArray"][i]["player_id"].asUInt()-1)[cmd["CommandArray"][i]["target_index"].asUInt()], pos);
                unique_ptr<engine::Command> ptr_deplacement(new engine::Move_Command(deplacement));
                myEngine.addCommand(move(ptr_deplacement));
                myEngine.update();
            }
            else if(cmd["CommandArray"][i]["id"].asUInt()==engine::ATTACK ) {
                int targetPID= (cmd["CommandArray"][i]["player_id"].asUInt()==2)?1:2;
                engine::Attack_Command attack(*myEngine.getState().
                getListCharacters(cmd["CommandArray"][i]["id"].asUInt()-1)[cmd["CommandArray"][i]["attacker_index"].asUInt()],
                    *myEngine.getState().getListCharacters(targetPID-1)[cmd["CommandArray"][i]["target_index"].asUInt()]);
                unique_ptr<engine::Command> ptr_attack(new engine::Attack_Command(attack));
                myEngine.addCommand(move(ptr_attack));
                myEngine.update();
            }
            else if(cmd["CommandArray"][i]["id"].asUInt()==engine::CAPAB ){

            }
            else if(cmd["CommandArray"][i]["id"].asUInt()==engine::FINISH_TURN ){
                engine::Finish_Turn_Command finish;
                unique_ptr<engine::Command> ptr_finish(new engine::Finish_Turn_Command(finish));
                myEngine.addCommand(move(ptr_finish));
                myEngine.update();
            }else{
                cout<<"COMMAND NOT FOUND"<<endl;
            }
                
        }
        
        cout << "END OF 1 MIN RECORD"<<endl;
        // END WAITING TO BE CLOSED
        while(1){
            while(window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                 window.close();
                 break;
                }
            } 
             
        }
    }

}

