#include "RandomAI.h"
#include "engine.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>



using namespace ai;
using namespace std;
using namespace state;
using namespace engine;


void RandomAI::run(engine::Engine& myEngine){


    int targetPlayerID= (this->getNbplayers()==2)? 1:2;

    // random Selection of the character
    int randomCharSelected = selectCharacter(myEngine.getState());
    Character &selectedChar = *myEngine.getState().getListCharacters(this->getNbplayers()-1)[randomCharSelected];
    unique_ptr<engine::Command> selectCommand(new Sel_Char_Command(selectedChar));
    myEngine.addCommand(move(selectCommand));myEngine.update();

    // ennemy character in range ?
    if(selectedChar.allowedAttackTarget(myEngine.getState()).size() > 0){

        // random selection of target in range
        int random = selectedChar.allowedAttackTarget(myEngine.getState())[rand() %
                (selectedChar.allowedAttackTarget(myEngine.getState()).size())];
        Character& targetChar= *myEngine.getState().getListCharacters(targetPlayerID-1)[random];

        unique_ptr<Command> ptr_ac(new Attack_Command(selectedChar,targetChar));
        myEngine.addCommand(move(ptr_ac)); myEngine.update();


        if (rand()%2){ // Choose randomly to move or not
            int mvLeft= selectedChar.getMovementLeft();
            
            // move until mouvement left =0
            while (mvLeft>0)
            {   
                Position randPosToMove (selectedChar.getPosition().getNearPositions()[rand()%4]);
                unique_ptr<Command> ptr_mv ( new Move_Command(selectedChar,randPosToMove));
                myEngine.addCommand(move(ptr_mv));myEngine.update();
                mvLeft--;

            }
            
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
                Character& targetChar1= *myEngine.getState().getListCharacters(targetPlayerID-1)[random1];

                unique_ptr<Command> ptr_ac1(new Attack_Command(selectedChar,targetChar1));
                myEngine.addCommand(move(ptr_ac1)); myEngine.update();
                break; // sort du while

             }

            //mvLeft1=selectedChar.getMovementLeft();
            mvLeft1--;
        }
    
    }
        unique_ptr<Command> ptr_ft1( new Finish_Turn_Command());
        myEngine.addCommand(move(ptr_ft1));myEngine.update();

}


// Return tab of index of all alive character
int RandomAI::selectCharacter (state::State& state){
    std::vector<int> posibleIndex;

    for(unsigned int i = 0; i < state.getListCharacters(this->getNbplayers()-1).size(); i++){
        state::Character &charac = *state.getListCharacters(this->getNbplayers()-1)[i];
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
