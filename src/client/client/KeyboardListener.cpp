#include <string>
#include "../client.h"
#include "../shared/state.h"
#include "../shared/engine.h"
#include <iostream>
#include <unistd.h>
#include <queue>
using namespace client;
using namespace state;
using namespace engine;
using namespace std;


// For now commented not finish yet

KeyboardListener::KeyboardListener(engine::Engine &refEngine):myEngine(refEngine)
{
    curTargIndex=0;
    curSelIndex=0;
}


void KeyboardListener::InputManager(sf::Event event){
    state::CurActionID curAID=myEngine.getState().getCurAction();
    int curPID=myEngine.getState().getCurPlayerID();
    
    if( curAID==IDLE){
        cursorIDLE(curPID);

        // for now i am tired so I let this code
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
            for (auto& charac: myEngine.getState().getListCharacters(curPID-1)){
            if(charac->getStatus()==SELECTED){
                myEngine.getState().setCurAction(state::MOVING);
            }
            }  
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            for (auto& charac: myEngine.getState().getListCharacters(curPID-1)){
                if(charac->getStatus()==SELECTED){
                    myEngine.getState().setCurAction(state::ATTACKING); 
                }
            }  
        }
    

    }else if(curAID==state::MOVING){
        state::Character& selCharm= 
        *myEngine.getState().getListCharacters(curPID-1)[SelectedChar(curPID)];
        MOVING(selCharm);
        // Changing to Attacking Mode
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            myEngine.getState().setCurAction(state::ATTACKING);
            // Some Init stuff
            if(selCharm.allowedAttackTarget(myEngine.getState()).size()){
                int targPlayer= (myEngine.getState().getCurPlayerID()==2)?1:2;
                for(auto&charac: myEngine.getState().getListCharacters(targPlayer-1) ){
                    if( charac->getStatus()!=DEATH){
                        for(auto& pos: selCharm.allowedAttackPos(myEngine.getState())){
                            if(pos.equals(charac->getPosition()))
                                myEngine.getState().getCursor().setPosition(charac->getPosition());
                        }
                    }
                        
                }       
                
            }
        }
            
    }else if(curAID==ATTACKING){
       
        state::Character& selChar= 
        *myEngine.getState().getListCharacters(curPID-1)[SelectedChar(curPID)];
        cursorAttacking(selChar,curPID);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            myEngine.getState().setCurAction(state::MOVING);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        myEngine.getState().setCurAction(IDLE);
        unique_ptr<Command> ptr_ft(new Finish_Turn_Command());
        myEngine.addCommand(move(ptr_ft));
    }

    myEngine.update();
    
}

void KeyboardListener::cursorIDLE(int curPlayerID){

    std::vector<unique_ptr<Character>>& listChar=  myEngine.getState().getListCharacters(curPlayerID-1);
    state::Cursor& cur= myEngine.getState().getCursor();
    std::vector<int> aliveChar;
    for(auto& charac: listChar){
        if(charac->getStatus()!=DEATH)
            aliveChar.push_back(charac->getIndex());
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        curSelIndex=(curSelIndex+1)%aliveChar.size();    
        cur.setPosition(listChar[aliveChar[curSelIndex]]->getPosition());
      
    }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        curSelIndex=(curSelIndex-1)%listChar.size();
        if(curSelIndex<0) curSelIndex=listChar.size()-1;  
        cur.setPosition(listChar[aliveChar[curSelIndex]]->getPosition());
  
    }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        // select the character
        unique_ptr<Command> ptr_sel( new Sel_Char_Command(*listChar[curSelIndex]));
        myEngine.addCommand(move(ptr_sel));
    }


}

void KeyboardListener::MOVING(state::Character& selChar){
    
     state::Cursor& cur= myEngine.getState().getCursor();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        state::Position pos{selChar.getPosition().getX(),selChar.getPosition().getY()-1};
        if(selChar.getMovementLeft()>0) cur.setPosition(pos);
        unique_ptr<Command> ptr_mv( new Move_Command(selChar,pos));
        myEngine.addCommand(move(ptr_mv));
        
          
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        state::Position pos{selChar.getPosition().getX()+1,selChar.getPosition().getY()};
        if(selChar.getMovementLeft()>0) cur.setPosition(pos);
        unique_ptr<Command> ptr_mv( new Move_Command(selChar,pos));
        myEngine.addCommand(move(ptr_mv));

    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        state::Position pos{selChar.getPosition().getX(),selChar.getPosition().getY()+1};
        if(selChar.getMovementLeft()>0) cur.setPosition(pos);
        unique_ptr<Command> ptr_mv( new Move_Command(selChar,pos));
        myEngine.addCommand(move(ptr_mv));

    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        state::Position pos{selChar.getPosition().getX()-1,selChar.getPosition().getY()};
        if(selChar.getMovementLeft()>0) cur.setPosition(pos);
        unique_ptr<Command> ptr_mv( new Move_Command(selChar,pos));
        myEngine.addCommand(move(ptr_mv));
    }
    
}

void KeyboardListener::cursorAttacking(state::Character& selChar,int CurPLayerID){
    int tarPlayerID= (CurPLayerID==2)?1:2;
    std::vector<unique_ptr<Character>>& listTarChar=  myEngine.getState().getListCharacters(tarPlayerID-1);
    state::Cursor& cur= myEngine.getState().getCursor();
    std::vector<int> charIndexInRange= selChar.allowedAttackTarget(myEngine.getState());

    if(charIndexInRange.size()){
         if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            curTargIndex= (curTargIndex+1)%charIndexInRange.size();
            cur.setPosition(listTarChar[charIndexInRange[curTargIndex]]->getPosition());
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            curTargIndex= (curTargIndex-1)%charIndexInRange.size();
            cur.setPosition(listTarChar[charIndexInRange[curTargIndex]]->getPosition());
        }
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        if(!selChar.getAttacked()){
            unique_ptr<Command> ptr_ac (new Attack_Command(selChar,*listTarChar[charIndexInRange[curTargIndex]]));
            myEngine.addCommand(move(ptr_ac));
            selChar.setAttacked(true);
        }
        
    }
   

}

int KeyboardListener::SelectedChar(int curPlayerID){
    int selCharIndex;
    for(auto&charact: myEngine.getState().getListCharacters(curPlayerID-1)){
        if( charact->getStatus()==state::SELECTED)
            return charact->getIndex();

    }
}