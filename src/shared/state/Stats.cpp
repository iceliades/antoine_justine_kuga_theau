#include "Stats.h"


namespace state {
    Stats::Stats() {
        Agility = 8;
        Arcane  = 8;
        Courage = 8;
        Intelligence = 8;
        Stamina = 8;
        Strength = 8;
    }

    Stats::Stats(int Agility, int Arcane, int Courage, int Intelligence, int Stamina, int Strength){
        this->Agility=Agility;
        this->Arcane=Arcane;
        this->Courage=Courage;
        this->Intelligence=Intelligence;
        this->Stamina=Stamina;
        this->Strength=Strength;
    }
    Stats::~Stats() {

    }

//------------------------------------------------- Setters ------------------------------------------------------------

    void Stats::setAgility(int agility) {
        Agility = agility;
    }
    void Stats::setArcane(int arcane) {
        Arcane = arcane;
    }
    void Stats::setCourage(int courage) {
        Courage = courage;
    }
    void Stats::setIntelligence(int intelligence) {
        Intelligence = intelligence;
    }
    void Stats::setStamina(int stamina) {
        Stamina = stamina;
    }
    void Stats::setStrength(int strength) {
        Strength = strength;
    }


//------------------------------------------------- Getters ------------------------------------------------------------

    int Stats::getAgility()  {
        return Agility;
    }
    int Stats::getArcane()  {
        return Arcane;
    }
    int Stats::getCourage()  {
        return Courage;
    }
    int Stats::getIntelligence()  {
        return Intelligence;
    }
    int Stats::getStamina()  {
        return Stamina;
    }
    int Stats::getStrength()  {
        return Strength;
    }


}