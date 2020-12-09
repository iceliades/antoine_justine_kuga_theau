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
/*
KeyboardListener::KeyboardListener(engine::Engine &engine)
{
    engine;
}



Keyboard::InputManager(sf::Event event){
    state::CurActionID curActionID=myEgnine.getStat().getCurAction();
    state:: curPlayerID curPID=myEngine.getState().getCurPlayerID();
    switch (curActionID)
    {
    case IDLE
            cursorIDLE(curPID,event);
        break;
    case MOVING
            state::Character& selectedChar= 
            *myEngine.getState().getLisCharacter(curPID)[selectedChar(curPID)];
            cursorMOVING(selectedChar, sf::Event event);
            // RIGHT LEFT UP DOWN
        break;
    case ATTACKING
            cursorAttacking(curPID,event);
        break;
    
    }


}

Keyboard::cursorIDLE(curPlayerID,sf::Event event){

    int curIndex=0;
    std::Vecotr<unique_ptr<Character>>& listChar=  myEngine.getState().getListCharacters(curPlayerID-1);
    state::Cursor& cur= myEngine.getState().getCursor();

    if( event==RIGHT){
        curIndex++;
        cur.setPosition(listChar[curIndex%lisChar.size()]->getPosition());
    }else if( event==LEFT){
        curIndex--;
        cur.setPosition(listChar[curIndex%lisChar.size()]->getPosition());
    }

}

Keyboard::MOVING(state::Character& selChar, sf::Event event){
    
     state::Cursor& cur= myEngine.getState().getCursor();
    switch (event)
    {
    case UP
        Position pos{selChar.getPosition().getX(),--selChar.getPosition().getY()}
        // ad comand
        cursor.setPosition(pos);
        break;
    case RIGHT
        Position pos{++selChar.getPosition().getX(),selChar.getPosition().getY()}
        cursor.setPosition(pos);
        break;
    case DOWN
        Position pos{selChar.getPosition().getX(),++selChar.getPosition().getY()}
        cursor.setPosition(pos);
        break;
    case LEFT
        Position pos{--selChar.getPosition().getX(),selChar.getPosition().getY()}
        cursor.setPosition(pos);
        break;
    
    }
    
}

Keyboard::cursorAttacking(state::Character& selChar,CurPLayerID){
    int tarPlayerID= (curPlayerID==2)?1:2;
    int curIndex=0;
    std::Vecotr<unique_ptr<Character>>& listTarChar=  myEngine.getState().getListCharacters(tarPlayerID-1);
    state::Cursor& cur= myEngine.getState().getCursor();
    std::vector<int> charIndexInRange;
    for(auto& tarChar: listTarCHar){
        for(auto& pos: selChar.allowAttackPos())
        {
            if(pos.equals(tarChar.pos()))
                charIndexInRange.push_back(tarChar.getIndex());
        }
    }

    if( event==RIGHT){
        curIndex++;
        cur.setPosition(listTarChar[charIndexInRange[curIndex%charIndexInRange.size()]]->getPosition());
    }else if( event==LEFT){
        curIndex--;
        cur.setPosition(listTarChar[curIndex%charIndexInRange.size()]->getPosition());
    }

}

int KeyboardListener::SelectedChar(curPlayerID){
    int selCharIndex;
    for(auto&charact: myEngine.getState().getListCharacter(curPlayerID-1)){
        if( charact.getStatus()==state::SELECTED)
            return charact.getIndex();

    }
}*/