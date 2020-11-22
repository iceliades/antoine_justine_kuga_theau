#include "Attack_Command.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;


Attack_Command::Attack_Command(Character& refAttacker, Character& refTarget) : attacker(refAttacker), target(refTarget)
{
	Id = ATTACK;	
}

Attack_Command::~Attack_Command(){}


void Attack_Command::exec(state::State& curState)
{
	cout << attacker.getName() << "is trying to attack" << target.getName() << endl;
	cout << "Actual health of " << target.getName() << ": " << target.getHealth() << endl;
	
	default_random_engine generator
	bernoulli_distribution precision(attacker.getPrecision());
	bernoulli_distribution dodge(1-target.getDodge());
    

	for(auto& index: attacker.allowedAttackTarget(curState)){
		if( index==target.getIndex()){
			int chardmg= attacker.getCharWeap()->getDammages();
			// need to produce the final using dodge and precision
			if (precision(generator) && dodge(generator)){
				nt newtarHealth= target.getHealth()- chardmg;
				target.setNewHealth(newtarHealth);
				
				if (target.getHealth()<= 0){
					target.setStatus(DEATH);
					cout<<"U KILLED THE CHARACTER"<<target.getName()<<endl;
				}
				
				cout << "THE TARGET HEALTH"<< target.getHealth()<<endl;
				cout<<"\n";
			}
			else cout << "Sorry, you missed... Retry next turn or die before..." << endl;
		}
	}	
	
	
	


}


