#include "Stats.h"


namespace state {
    Stats::Stats() {
        int Agility     = 8;
        int Arcane     = 8;
        int Courage     = 8;
        int Intelligence     = 8;
        int Stamina     = 8;
        int Strength     = 8;
    }
    Stats::Stats(int agility, int arcane, int courage, int intelligence, int stamina, int strength) {
        Agility = agility;
        Arcane = arcane;
        Courage = courage;
        Intelligence = intelligence;
        Stamina = stamina;
        Strength = strength;

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

    int Stats::getAgility() const {
        return Agility;
    }
    int Stats::getArcane() const {
        return Arcane;
    }
    int Stats::getCourage() const {
        return Courage;
    }
    int Stats::getIntelligence() const {
        return Intelligence;
    }
    int Stats::getStamina() const {
        return Stamina;
    }
    int Stats::getStrength() const {
        return Strength;
    }


}