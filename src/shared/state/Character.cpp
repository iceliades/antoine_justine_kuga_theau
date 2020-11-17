#include "Character.h"
#include "Player.h"
#include "State.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;


Character::Character(CharacterTypeID id, std::string name, int x, int y, int char_tileCode) {

    this->tileCode = char_tileCode;
    position.setX(x);
    position.setY(y);

    TypeID = id;
    Name = name;
    Status = AVAILABLE;
    charWeap= new Weapon(SWORD);
    effect = Effect();
    Movement = 5;
    MovementLeft= 5;
    PlayerID = 0;//Player->getListCharacters().size;
    direction = DOWN;

    switch (id) {
        case (CROOK) :
            Health = 100;
            Precision = 2.0;
            Dodge = 0.0;
            //  stats.setIntelligence(stats.getIntelligence()+1);
        break;
        case (KNIGHT) :
            Health = 80;
            Precision = 3.0;
            Dodge = 0.0;
            //  stats.setCourage(stats.getCourage()+1);
        break;
        case (ELF) :
            Health = 80;
            Precision = 3.0;
            Dodge = 0.0;
            //  stats.setAgility(stats.getAgility()+1);
        break;
        case (NATIVE) :
            Health = 80;
            Precision = 3.0;
            Dodge = 0.0;
            //  stats.setArcane(stats.getArcane()+1);
        break;
        case (DWARF) :
            Health = 80;
            Precision = 3.0;
            Dodge = 0.0;
            //  stats.setStamina(stats.getStamina()+1);
        break;
        case (PIRATE) :
            Health = 80;
            Precision = 3.0;
            Dodge = 0.0;
            //  ANNOYING WE NEED A WAY TO GET THE PLAYER'S CHOICE
        break;
        case (TROLL) :
            Health = 80;
            Precision = 3.0;
            Dodge = 0.0;
            //  stats.setStrength(stats.getStrength()+1);
        break;

}
}
Character::~Character(){
    delete charWeap;
}

//------------------------------------------------- Setters ------------------------------------------------------------
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

void Character::setEffect (bool Immobilised,bool Stunned,bool Disarmed){
    effect.setImmobilised(Immobilised);
    effect.setStunned(Stunned);
    effect.setDisarmed(Disarmed);
}

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


void Character::setTypeID(CharacterTypeID TypeID){
    // TypeID can't change
    cout << "What are you doing ?!\n";
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

//------------------------------------------------- Getters ------------------------------------------------------------
CharacterTypeID Character::getTypeID() {
    return TypeID;
}

std::string   Character::getName (){
    return Name;
}

CharacterStatusID Character::getStatus (){
    return Status;
}

int Character::getMovement (){
    return Movement;
}

int Character::getHealth (){
    return Health;
}

float Character::getDodge (){
    return Dodge;
}

float Character::getPrecision (){
    return Precision;
}

Effect& Character::getEffect (){
    return effect;
}
Stats& Character::getStats (){
    return stats;
}
Weapon* Character::getCharWeap (){
    return charWeap;
}

//----------------------------------------------------- Misc -----------------------------------------------------------
bool Character::isMapCell(){
    return false;
}




