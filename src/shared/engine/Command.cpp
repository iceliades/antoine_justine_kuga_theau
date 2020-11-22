  
#include "Command.h"
using namespace engine;

engine::CommandID Command::getId(){
	return Id;
}

void Command::setId(engine::CommandID id){
	Id = id;
}
