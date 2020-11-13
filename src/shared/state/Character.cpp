#include "Character.h"
#include "State.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;


Character::Character(CharacterTypeID id, std::string name, int x, int y, int char_tileCode){

    this->tileCode=char_tileCode;
    TypeID=id;
    Name= name;
    Status= AVAILABLE;
    //charWeap= new Weapon(SWORD);
    Movement = 5;

    if (id==CROOK){
        Health=100;
        Precision=2; 
        Dodge = 0;
       // stats.setAgility(stats.getAgility()+1);// Taxon bonus
       
    }else if (id==KNIGHT)
    {
        Health=80;
        Precision=3; 
        Dodge = 0;
      //  stats.setAgility(stats.getAgility()+1);
        
    }else if (id==ELF){

    }else if (id==NATIVE){

    }else if (id==DWARF){

    }else if (id==PIRATE)
    {
        /* code */
    }else if (id==TROLL)
    {
        /* code */
    }
    
}
Character::~Character(){
    //delete charWeap;
}


// Getters
CharacterTypeID Character::getTypeID() {return TypeID;}
std::string   Character::getName (){return Name;}
CharacterStatusID Character::getStatus (){return Status;};
int Character::getMovement (){return Movement;}
int Character::getHealth (){return Health;}
float Character::getDodge (){return Dodge;}
float Character::getPrecision (){return Precision;}

/*Effect& Character::getEffect (){
    Effect &refEff = effect;
    return refEff;
}
Stats& Character::getStats (){
    Stats &refStats = stats;
    return refStats;
}
Weapon* Character::getCharWeap (){
    return charWeap;
}
*/
bool Character::isMapCell(){
    return false;
}

// Setters
void Character::setHealth ( int Stamina,  int Strength){
    
    Health= 3*Stamina + 2*Strength;
}

void Character::setMovementBonus (int Courage, int Stamina){
    Movement= int(5+ Courage/12 + Stamina/12);
}

void Character::setDodge (int Agility, int Intelligence){
    Dodge= (Agility+Intelligence)/60;
}

void Character::setPrecision ( int Agility, int Intelligence, int Strength, int Arcane){
    Precision= (Agility+Intelligence+Strength+Arcane)/60;
}
/*void Character::setEffect (bool Immobilised,bool Stunned,bool Disarmed){
    effect.setImmobilised(Immobilised);
    effect.setStunned(Stunned);
    effect.setDisarmed(Disarmed);
};

void Character::setCharWeap (Weapon* w){
    charWeap=w;
}

void Character::setStats (int Agility, int Arcane, int Courage, int Intelligence, int Stamina, int Strength){
    stats.setAgility(Agility);
    stats.setArcane(Arcane);
    stats.setCourage(Courage);
    stats.setIntelligence(Intelligence);
    stats.setStamina(Stamina);
    stats.setStrength(Strength);
}
*/

void Character::setTypeID(CharacterTypeID TypeID){
    // TypeID can't change
}
void Character::setName(const std::string& Name){
    this->Name=Name;
}
void Character::setStatus(CharacterStatusID Status){
    this->Status=Status;
}
void Character::setMovement(int Movement){
    this->Movement=Movement;
}


