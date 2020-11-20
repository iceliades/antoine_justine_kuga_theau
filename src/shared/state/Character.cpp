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
    Health = 100;
    Dodge = 0.1;
    Precision = 0.7;

    switch (id) {
        case (CROOK) :
            stats.setIntelligence(stats.getIntelligence()+1);
        break;
        case (KNIGHT) :
            stats.setCourage(stats.getCourage()+1);
        break;
        case (ELF) :
            stats.setAgility(stats.getAgility()+1);
        break;
        case (NATIVE) :
            stats.setArcane(stats.getArcane()+1);
        break;
        case (DWARF) :
            stats.setStamina(stats.getStamina()+1);
        break;
        case (PIRATE) :
            /*std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution(1,6);
            int dice_roll = distribution(generator);
            // Pirate and Gambling, name a better duo
            switch(dice_roll){
                case(1):
                    stats.setAgility(stats.getAgility()+1);
                case(2):
                    stats.setArcane(stats.getArcane()+1);
                case(3):
                    stats.setCourage(stats.getCourage()+1);
                case(4):
                    stats.setIntelligence(stats.getIntelligence()+1);
                case(5):
                    stats.setStamina(stats.getStamina()+1);
                case(6):
                    stats.setStrength(stats.getStrength()+1);
            }*/

        break;
        case (TROLL) :
            stats.setStrength(stats.getStrength()+1);
        break;

}
}
Character::~Character(){
    delete charWeap;
}

//------------------------------------------------- Setters ------------------------------------------------------------

void Character::setCharWeap (Weapon* w){
    charWeap=w;
}

void Character::setDodge (int Agility, int Intelligence){
    Dodge= (Agility+Intelligence)/60;
}

void Character::setEffect (bool Immobilised,bool Stunned,bool Disarmed){
    effect.setImmobilised(Immobilised);
    effect.setStunned(Stunned);
    effect.setDisarmed(Disarmed);
}

void Character::setHealth ( int Stamina,  int Strength){
    Health= 3*Stamina + 2*Strength;
}

void Character::setIndex(int Index) {
    this->Index=Index;
}

void Character::setName(const std::string& Name){
    this->Name=Name;
}

void Character::setMovement(int Movement){
    this->Movement=Movement;
}

void Character::setMovementBonus (int Courage, int Stamina){
    Movement= int(5+ Courage/12 + Stamina/12);
}


void Character::setPrecision ( int Agility, int Intelligence, int Strength, int Arcane){
    Precision= (Agility+Intelligence+Strength+Arcane)/60;
}
void Character::setStats (int Agility, int Arcane, int Courage, int Intelligence, int Stamina, int Strength){
    stats.setAgility(Agility);
    stats.setArcane(Arcane);
    stats.setCourage(Courage);
    stats.setIntelligence(Intelligence);
    stats.setStamina(Stamina);
    stats.setStrength(Strength);
}

void Character::setStatus(CharacterStatusID Status){
    this->Status=Status;
}

void Character::setTypeID(CharacterTypeID TypeID){
    // TypeID can't change
    cout << "What are you doing ?!\n";
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

int Character::getIndex() const {
    return Index;
}

//----------------------------------------------------- Misc -----------------------------------------------------------
bool Character::isMapCell(){
    return false;
}

void Character::attack(Character &target) {
    // maybe handled by engine un-coded because conflicts may arise
}
void Character::move(State &state, Direction direction) {
    // maybe handled by engine un-coded because conflicts may arise
}




