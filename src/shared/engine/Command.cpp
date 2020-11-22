  
#include "Command.h"
using namespace engine;

CommandID Command::getId(){
	return Id;
}

void Command::setID(CommandID Id){
	this->Id = Id;
}
