#include "Attack_Command.h"
#include <iostream>
#include <random>

using namespace engine;
using namespace state;
using namespace std;


Attack_Command::Attack_Command(Character& refAttacker, Character& refTarget) : attacker(refAttacker), target(refTarget)
{
	Id = ATTACK;	
}


void Attack_Command::exec(state::State& curState)
{
	cout << attacker.getName() << "is Attacking" << target.getName() << endl;
	/*Setting the probabilities*/
	int pre(attacker.getPrecision()), dod(target.getDodge());
	random_device         rdev{};
	default_random_engine generator(rdev());
	bernoulli_distribution precision(pre);
	bernoulli_distribution dodge(1-dod);
    

	for(auto& index: attacker.allowedAttackTarget(curState)){
		if( index==target.getIndex() && attacker.getPlayerID()!=target.getPlayerID()){
			int chardmg= attacker.getCharWeap()->getDammages();
			// need to produce the final using dodge and precision

			if (precision(generator) && dodge(generator)){
				int newtarHealth= target.getHealth()- chardmg;
				target.setNewHealth(newtarHealth);
				
				if (target.getHealth()<= 0){
					target.setStatus(DEATH);
					cout<<"U KILLED THE CHARACTER"<<target.getName()<<endl;
				}
				
				cout << "THE TARGET HEALTH"<< target.getHealth()<<endl;
				cout<<"\n";
			}else{
				int newtarHealth= target.getHealth()- (chardmg-int((dod/2)*chardmg));
				target.setNewHealth(newtarHealth);
				
				if (target.getHealth()<= 0){
					target.setStatus(DEATH);
					cout<<"U KILLED THE CHARACTER"<<target.getName()<<endl;
				}
				
				cout << "THE TARGET HEALTH"<< target.getHealth()<<endl;
				cout<<"\n";
			}
			
				
		}else{
			cout<<"You can't attack this element sorry buddy"<<endl;;
		}
	}	

}


