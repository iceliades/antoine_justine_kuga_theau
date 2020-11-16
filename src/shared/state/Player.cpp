#include "Player.h"
#include <iostream>

using namespace std;
using namespace state;



Player::Player(int id ){
    Id= id; 
    Name= "Player" + to_string(id);
    
}
Player::Player(int id, std::string name){
    Id= id; 
    Name= name;
}   

Player::~Player(){}

// getters and setters
int Player::getId(){ return Id;}
std::string Player::getName(){return Name;}
void Player::setName(std::string nm){ Name=nm;}
void Player::setID(int id){Id=id;}

std::vector<std::unique_ptr<Character>>& Player::getListCharacters(){
    return listCharacters;
}




void Player::addCharacter(std::unique_ptr<Character> ptr_character){
    listCharacters.push_back(std::move(ptr_character));
}



void Player::deleteCharacter(Character& character){
    for(unsigned int i=0; i<listCharacters.size(); i++){
        // Can be optimized
        if(listCharacters[i]->getPosition().getX() == character.getPosition().getX() && listCharacters[i]->getPosition().getY()== character.getPosition().getY()){
            listCharacters.erase(listCharacters.begin() + i);
        }
    }
}

