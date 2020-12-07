#include "Command_Client_Hello.h"
#include <iostream>


using namespace client;
using namespace std;


Command_Client_Hello::Command_Client_Hello() {
}
Command_Client_Hello::~Command_Client_Hello(){
}
void Command_Client_Hello::execute() {
    cout << "Bonjour le monde!" << endl;
}
