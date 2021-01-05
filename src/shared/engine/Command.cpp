  
#include "Command.h"
using namespace engine;

engine::CommandID Command::getId(){
	return Id;
}

void Command::setID(CommandID id){
	Id = id;
}

