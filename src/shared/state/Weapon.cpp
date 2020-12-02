#include "Weapon.h"
#include <iostream>


using namespace std;
using namespace state;


Weapon::Weapon(WeaponID id){
    Owner= "Player1";
    switch(id){
        
        case SWORD: 
            Dammages=13; MinRange=1; MaxRange=2;break;

        case AXE: 
            Dammages=14; MinRange=1; MaxRange=1.5;break;

        case SPEAR:
            Dammages=12; MinRange=1; MaxRange=2.5; break;

        case BOW:
            Dammages=6; MinRange=2; MaxRange=8;break;

        case CROSSBOW:
            Dammages=7; MinRange=2; MaxRange=7;break;

        case SLING:
            Dammages=8; MinRange=2; MaxRange=6.5;break;

        case WAND:
            Dammages=10; MinRange=3; MaxRange=4.5;break;

        case STICK:
            Dammages=11; MinRange=3; MaxRange=4;break;
            
        case STRAP:
            Dammages=9; MinRange=3; MaxRange=5;break;
        default:
            break;

    }


}

Weapon::~Weapon(){}

// getters
int Weapon::getDammages(){ return Dammages;}
float Weapon::getMinRange(){return MinRange;}
float Weapon::getMaxRange(){return MaxRange;}
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
