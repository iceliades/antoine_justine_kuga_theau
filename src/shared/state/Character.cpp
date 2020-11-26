#include "Character.h"
#include "Player.h"
#include "State.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <random>

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
	this->Capab.push_back(0);
	
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
        case (TROLL) :
            stats.setStrength(stats.getStrength()+1);
            break;
        case (PIRATE) :
            std::default_random_engine generator;
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
            }
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
    Dodge= 0.1 * pow((Agility+Intelligence-16),2)/196; // use pow to handle doubles and floats properly
}

void Character::setEffect (bool Immobilised,bool Stunned,bool Disarmed){
    effect.setImmobilised(Immobilised);
    effect.setStunned(Stunned);
    effect.setDisarmed(Disarmed);
}

void Character::setHealth ( int Stamina,  int Strength){
    Health= 3*Stamina + 2*Strength;
}
void Character::setNewHealth(int newHealth){ this->Health= newHealth;}

void Character::setIndex(int Index) {
    this->Index=Index;
}

void Character::setName(const std::string& Name){
    this->Name=Name;
}

void Character::setMovement(int Movement){
    this->Movement=Movement;
}
void Character::setMovementLeft(int movement){
    this->MovementLeft=movement;

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

void Character::setPlayerID(int PlayerID){
    this->PlayerID=PlayerID;
}

void Character::setCapused(bool use) {Capused = use;}

void Character::setCapab(int val, int pos) {this->Capab[pos] = val;}

//------------------------------------------------- Getters ------------------------------------------------------------
CharacterTypeID Character::getTypeID() {
    return TypeID;
}

std::string Character::getName (){
    return Name;
}

CharacterStatusID Character::getStatus (){
    return Status;
}

int Character::getMovement (){
    return Movement;
}
int Character::getMovementLeft(){
    return MovementLeft;
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

int Character::getPlayerID(){
    return this->PlayerID;
}

std::vector<int>& Character::getCapab()
{
	return Capab;
}

bool Character::getCapused() {return Capused;}

//----------------------------------------------------- Misc -----------------------------------------------------------
bool Character::isMapCell(){
    return false;
}

void Character::addCapab(int compt)
{
	Capab.push_back(move(compt));
}

std::vector<Position> Character::allowedMove(State& state){
    
    std::vector<Position> allowedPos;

    for (int y=0; y<=MovementLeft;y++){
        for (int x=y-MovementLeft; x<=MovementLeft-y;x++){
            Position pos(this->position.getX()+x,this->position.getY()+y);
            allowedPos.push_back(pos);
            if (y !=0){
                Position posMirror(this->position.getX()+x,this->position.getY()-y);
                allowedPos.push_back(posMirror);
            }
        }
    }

    for (unsigned int indexPos=0; indexPos<allowedPos.size();indexPos++){
        if (allowedPos[indexPos].getX()<0 || allowedPos[indexPos].getY()<0
        || allowedPos[indexPos].getX()>state.getMap()[0].size()
        || allowedPos[indexPos].getY()>state.getMap().size())
            allowedPos.erase(allowedPos.begin()+indexPos);

        for (auto &line: state.getMap()){
            if( line[0]->getPosition().getY() != allowedPos[indexPos].getY())
                continue;
            for (auto &mapCell: line){
                if (mapCell->getPosition().getX() != allowedPos[indexPos].getX())
                    continue;
                if (mapCell->getPosition().equals(allowedPos[indexPos])
                &&(mapCell->isSpace()==false || mapCell->isOccupied(state) !=-1) )
                    allowedPos.erase(allowedPos.begin()+indexPos);

            }
        }         
    }

    return allowedPos;
}


// Return all the positon the character is allowed to ttack
std::vector<Position> Character::allowedAttackPos(State &state){
   vector<Position> allowedAttackPos;
   int maxRange= this->charWeap->getMaxRange();
   for (int y=0; y<=maxRange;y++){
        for (int x=y-maxRange; x<=maxRange-y;x++){
            if (y==0 && x==0) // exclude character Position
                continue;
            Position pos(position.getX()+x,position.getY()+y);
            allowedAttackPos.push_back(pos);
            if (y !=0){
                Position posMirror(position.getX()+x,position.getY()-y);
                allowedAttackPos.push_back(posMirror);
            }
        }
    }
    return allowedAttackPos;
}

std::vector<int> Character::allowedAttackTarget (State& state){
    
    vector<int> posibleCharIndexes;
    std::vector<Position> charallowedAttackPos=allowedAttackPos(state); 
    
    for (unsigned int i=0; i< state.getListPlayers().size();i++){
        if( state.getCurPlayerID()!=(i+1)){
            for (unsigned int j=0; j< state.getListCharacters(i).size();j++){
                Character& charac = *state.getListCharacters(i)[j];
                if(charac.getPlayerID() != this->PlayerID && charac.getStatus() !=DEATH ){
                    for (unsigned int pos=0; pos<charallowedAttackPos.size(); pos++){
                        if(charallowedAttackPos[pos].equals(charac.getPosition())){
                            posibleCharIndexes.push_back(j);// return the index of the character
                        }
                    }
                }
            }

        }
        
    }
    return posibleCharIndexes;
}



