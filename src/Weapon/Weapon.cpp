
#include <iostream>
#include <string>
#include "Weapon.h"

using namespace std;
 
// Interface Weapon
class Weapon {
	public :
		// Constructeurs et destructeurs
		Weapon(){
				Dammages = 0;
				MaxRange = 0.;
				MinRange = 0.;
			}
		
		~Weapon(){}
		Weapon(string owner, string type, int dammages, float maxRange, float minRange){
				Owner = owner;
				Type = type;
				Dammages = dammages;
				MaxRange = maxRange;
				MinRange = minRange;
			}
			
		void afficher(){ // Juste pour moi et mes tests
			cout << "-----MON ARME : -----" << endl;
			cout << "Owner : " << Owner << endl;
			cout << "type : " << Type << endl;
			cout << "Dammages : " << Dammages << endl;
			cout << "Max : " << MaxRange << endl;
			cout << "Min : " << MinRange << endl;		
		}

		// Setters (public)
		void setOwner(string Name) { Owner = Name;}
		void setType(string type) { Type = type;}
		void setDammages(int dmg) { Dammages = dmg;}
		void setMaxRange(float prtM) { MaxRange = prtM;}
		void setMinRange(float prtm) { MinRange = prtm;}
	  
		// Getters (public)
		string getOwner() { return Owner;}
		string getType() { return Type;}
		int getDammages() { return Dammages;}
		float getMaxRange() { return MaxRange;}
		float getMinRange() { return MinRange;}
   
   // variables
	protected:
		string Owner;
		string Type;
		int Dammages;
		float MaxRange;
		float MinRange;
};
 






// Classes héritées

class Sword: public Weapon {
	public:
		// Constructeurs et destructeurs
		Sword(){
				Type = "Close Combat" ;
				Dammages = 13;
				MaxRange = 2;
				MinRange = 1;
			}
		~Sword(){}
};


class Spear: public Weapon {
   public:
		// Constructeurs et destructeurs
		Spear(){
				Type = "Close Combat" ;
				Dammages = 12;
				MaxRange = 2.5;
				MinRange = 1;
			}
		~Spear(){}
};


class Crossbow: public Weapon {
   public:
		// Constructeurs et destructeurs
		Crossbow(){
				Type = "Long shot" ;
				Dammages = 7;
				MaxRange = 7;
				MinRange = 2;
			}
		~Crossbow(){}
};


class Staff: public Weapon {
   public:
		// Constructeurs et destructeurs
		Staff(){
				Type = "Magic" ;
				Dammages = 11;
				MaxRange = 4;
				MinRange = 3;
			}
		~Staff(){}
};


class Wand: public Weapon {
   public:
		// Constructeurs et destructeurs
		Wand(){
				Type = "Magic";
				Dammages = 9;
				MaxRange = 5;
				MinRange = 3;
			}
		~Wand(){}
};


class Bracelets: public Weapon {
   public:
		// Constructeurs et destructeurs
		Bracelets(){
				Type = "Long shot" ;
				Dammages = 10;
				MaxRange = 4.5;
				MinRange = 3;
			}
		~Bracelets(){}
};


class Sling: public Weapon {
   public:
		// Constructeurs et destructeurs
		Sling(){
				Type = "Long shot" ;
				Dammages = 8;
				MaxRange = 6.5;
				MinRange = 2;
			}
		~Sling(){}
};


class Bow: public Weapon {
   public:
		// Constructeurs et destructeurs
		Bow(){
				Type = "Long shot" ;
				Dammages = 6;
				MaxRange = 7.5;
				MinRange = 2;
			}
		~Bow(){}
};


class Axe: public Weapon {
   public:
		// Constructeurs et destructeurs
		Axe(){
				Type = "Close Combat" ;
				Dammages = 14;
				MaxRange = 1.5;
				MinRange = 1;
			}
		~Axe(){}
};

