/*
 * Attack_Command.cpp
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


#include "engine.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;
using namespace engine;
using namespace state;

Attack_Command::Attack_Command(Character& newAttacker, Character& newTarget) : attacker(newAttacker), target(newTarget)
{
	Id = ATTACK;	
}

Attack_Command::~Attack_Command(){}

Json::Value serialize()
{
	Json::Value newCommand;
	newCommand["id"] = Id;
	newCommand["player"] = attacker.getPlayerId();
	newCommand["attacker"] = attacker.getTypeId();
	newCommand["target"] = target.getTypeId();
	
	return newCommand;
}

void exec(State& state)
{
	cout << attacker.getName() << "is attacking" << target.getName() << endl;
	
}

