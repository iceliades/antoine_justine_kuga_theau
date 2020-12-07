#include "Command_Client_Autre.h"
#include <iostream>

using namespace client;
using namespace std;


Command_Client_Autre::Command_Client_Autre() {
}
Command_Client_Autre::~Command_Client_Autre(){
}
void Command_Client_Autre::execute(){
    cout << "Veillez utiliser les commandes make unittest et make code-coverage depuis le dossier build" << endl;
}
