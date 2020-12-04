#include "RandomAI.h"
#include "engine.h"
#include "state.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>



using namespace ai;
using namespace std;
using namespace state;
using namespace engine;


void RandomAI::run(engine::Engine& myEngine){


    int targetPlayerID= (this->getNbplayers()==2)? 1:2;

    int randomCharSelected = selectCharacter(myEngine.getState());
    // always select someone
    Character &selectedChar = *myEngine.getState().getListCharacters(this->getNbplayers())[randomCharSelected];
    unique_ptr<engine::Command> selectCommand(new Sel_Char_Command(selectedChar));
    myEngine.addCommand(move(selectCommand));

    // ennemy character in range ?
    if(selectedChar.allowedAttackTarget(myEngine.getState()).size() > 0){
        int random = selectedChar.allowedAttackTarget(myEngine.getState())[(rand() %
                (selectedChar.allowedAttackTarget(myEngine.getState()).size()))];
        Character& targetChar= *myEngine.getState().getListCharacters(targetPlayerID)[random];

        unique_ptr<Command> ptr_ac(new Attack_Command(selectedChar,targetChar));
        myEngine.addCommand(move(ptr_ac)); myEngine.update();


        if (rand()%2){ // Choose randomly to move or finish turn
            int mvLeft= selectedChar.getMovementLeft();
            while (mvLeft>0)
            {   
                Position randPosToMove (selectedChar.getPosition().getNearPositions()[rand()%4]);
                unique_ptr<Command> ptr_mv ( new Move_Command(selectedChar,randPosToMove));
                myEngine.addCommand(move(ptr_mv));myEngine.update();
                mvLeft=selectedChar.getMovementLeft();

            }
            
            unique_ptr<Command> ptr_ft( new Finish_Turn_Command());
            myEngine.addCommand(move(ptr_ft));myEngine.update();
            
        }else{

            unique_ptr<Command> ptr_ft( new Finish_Turn_Command());
            myEngine.addCommand(move(ptr_ft));myEngine.update();
        }

    }else{

        int mvLeft1= selectedChar.getMovementLeft();
        while(mvLeft1>0){

            Position randPosToMove1 (selectedChar.getPosition().getNearPositions()[rand()%4]);
            unique_ptr<Command> ptr_mv1 ( new Move_Command(selectedChar,randPosToMove1));
            myEngine.addCommand(move(ptr_mv1));myEngine.update();
            

            if(selectedChar.allowedAttackTarget(myEngine.getState()).size() > 0){

                 int random1= selectedChar.allowedAttackTarget(myEngine.getState())[(rand() %
                (selectedChar.allowedAttackTarget(myEngine.getState()).size()))];
                Character& targetChar1= *myEngine.getState().getListCharacters(targetPlayerID)[random1];

                unique_ptr<Command> ptr_ac1(new Attack_Command(selectedChar,targetChar1));
                myEngine.addCommand(move(ptr_ac1)); myEngine.update();

                unique_ptr<Command> ptr_ft1( new Finish_Turn_Command());
                myEngine.addCommand(move(ptr_ft1));myEngine.update();
                break;

             }
            mvLeft1=selectedChar.getMovementLeft();
        }
        
    }

}


int RandomAI::selectCharacter (state::State& state){
    std::vector<int> posibleIndex;

    for(unsigned int i = 0; i < state.getListCharacters(this->getNbplayers()).size(); i++){
        state::Character &charac = *state.getListCharacters(this->getNbplayers())[i];
        if(charac.getPlayerID() == this->getNbplayers() && charac.getStatus() != DEATH)
            posibleIndex.push_back(i);
    }

    int randomNumber = rand() % posibleIndex.size();
    cout << "[";
    for(auto &index : posibleIndex){
        cout << index << ", ";
    }
    cout << "]" << endl;
    return posibleIndex[randomNumber];
}
