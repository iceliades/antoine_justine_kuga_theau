/*
 * Capab_Command.cpp
 * 
 * Copyright 2020 Vincent Ferrier <vincent@vincent-TravelMate-8331>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include "Capab_Command.h"
#include <iostream>
#include <random>

using namespace engine;
using namespace state;
using namespace std;

Capab_Command::Capab_Command(state::Character& refUser, state::Character& refTarget,
	state::Position& refTargetedPos) : user(refUser), target(refTarget), targetedPos(refTargetedPos)
{
	Id = CAPAB;
}


void Capab_Command::exec (state::State& curState)
{
	if (user.getCapab()[0] != 0) {cout << "You can't use your powers yet." << endl;}
	else 
	{
		cout << user.getName() << "is using his powers." << endl;
	
		user.setCapused(true);
		user.setCapab(3,0);
		CapabID cap = user.getCharWeap()->getCType();
	
		/*Setting the probabilities for arrow rain*/
		int pre(user.getPrecision()), dod(target.getDodge());
		random_device         rdev{};
		default_random_engine generator(rdev());
		bernoulli_distribution precision(pre);
		bernoulli_distribution dodge(1-dod);
	
		switch(cap)
		{
			case (IMMOBIL):
				target.setEffect(true, false, false);
				target.setMovementLeft(0);
				cout << target.getName() << "is immobilised." << endl;
				break;
			
			case (SRAIN):
	
				for(auto& index: user.allowedAttackTarget(curState)){
					if( index==target.getIndex()&& user.getPlayerID()!=target.getPlayerID()){
						int chardmg= user.getCharWeap()->getDammages();
						// need to produce the final using dodge and precision
						if (precision(generator) && dodge(generator)){
							int newtarHealth= target.getHealth()- int(3*(1-dod)*pre*chardmg);
							target.setNewHealth(newtarHealth);
							
							if (target.getHealth()<= 0){
								target.setStatus(DEATH);
								cout<<"U KILLED THE CHARACTER"<<target.getName()<<endl;
							}
							
							cout << "THE TARGET HEALTH"<< target.getHealth()<<endl;
							cout<<"\n";
						}else{
							int newtarHealth= target.getHealth()- int((3*(1-dod)*pre*chardmg)/2);
							target.setNewHealth(newtarHealth);
							
							if (target.getHealth()<= 0){
								target.setStatus(DEATH);
								cout<<"U KILLED THE CHARACTER"<<target.getName()<<endl;
							}
							
							cout << "THE TARGET HEALTH"<< target.getHealth()<<endl;
							cout<<"\n";
						}
					}else
					{
						cout<<"You can't attack this element sorry buddy";
					}
					
				}
				break;
			
			case (TELEPORT):
		
				cout << "User at " << user.getPosition().getX() << "," << user.getPosition().getY() << " will teleport" << endl;
				cout<<"\n";
				user.getPosition().setX(targetedPos.getX());
				user.getPosition().setY(targetedPos.getY());
				cout << "User teleported at " << user.getPosition().getX() << "," << user.getPosition().getY() << endl;
				break;		
		}
	}
}











