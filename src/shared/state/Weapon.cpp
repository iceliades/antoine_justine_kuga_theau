#include "Weapon.h"
#include <iostream>


using namespace std;
using namespace state;


Weapon::Weapon(WeaponID id){
    Owner= "Player1";
    switch(id){
        
        case SWORD: 
            Dammages=13; MinRange=1; MaxRange=2; typeCapab=IMMOBIL; break;

        case AXE: 
            Dammages=14; MinRange=1; MaxRange=1.5; typeCapab=IMMOBIL; break;

        case SPEAR:
            Dammages=12; MinRange=1; MaxRange=2.5; typeCapab=IMMOBIL; break;

        case BOW:
            Dammages=6; MinRange=2; MaxRange=8; typeCapab=SRAIN; break;

        case CROSSBOW:
            Dammages=7; MinRange=2; MaxRange=7; typeCapab=SRAIN; break;

        case SLING:
            Dammages=8; MinRange=2; MaxRange=6.5; typeCapab=SRAIN; break;

        case WAND:
            Dammages=10; MinRange=3; MaxRange=4.5; typeCapab=TELEPORT; break;

        case STICK:
            Dammages=11; MinRange=3; MaxRange=4; typeCapab=TELEPORT; break;
            
        case STRAP:
            Dammages=9; MinRange=3; MaxRange=5; typeCapab=TELEPORT; break;
        default:
            break;

    }


}

Weapon::~Weapon(){}

// getters
int Weapon::getDammages(){ return Dammages;}
float Weapon::getMinRange(){return MinRange;}
float Weapon::getMaxRange(){return MaxRange;}
CapabID Weapon::getCType(){return typeCapab;}
std::string Weapon::getOwner(){return Owner;}

//setters
void Weapon::setDammages(int dmg){
    Dammages=dmg;
}
void Weapon::setMaxRange(float prtM){
    MaxRange=prtM;
}
void Weapon::setMinRange(float prtm){
    MinRange= prtm;
}

void Weapon::setOwner(std::string Nom){
    Owner=Nom;
}
void Weapon::setTypeCapab(CapabID typeCapab){
    this->typeCapab= typeCapab;
}
