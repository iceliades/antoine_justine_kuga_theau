#include "Command_Client_Autre.h"
#include <iostream>

using namespace client;
using namespace std;


Command_Client_Play::Command_Client_Play() {
}
Command_Client_Play::~Command_Client_Play(){
}
void Command_Client_Play::execute(){
    cout <<" Cette commande est inexistante"<<endl;
    //cout << "Veillez utiliser les commandes make unittest et make code-coverage depuis le dossier build" << endl;
}
