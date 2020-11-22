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

using namespace engine;
using namespace state;
using namespace std;

Capab_Command::Capab_Command(state::Character& refUser, state::Character& refTarget) : user(refUser), target(refTarget)
{
	Id = CAPAB;
}

Capab_Command::~Capab_Command()
{
	
}

/*void Capab_Command::Exec (state::State& curState)
{
	cout << user.getName() << "is trying to use his powers on" << target.getName() << endl;
	
	for(auto& index: attacker.allowedAttackTarget(curState))
	{
		if(index==target.getIndex())
		{
			
		}
	}
}*/










