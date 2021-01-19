#include "Command_Client_Autre.h"
#include <iostream>

using namespace client;
using namespace std;


Command_Client_Autre::Command_Client_Autre() {
}
Command_Client_Autre::~Command_Client_Autre(){
}
void Command_Client_Autre::execute(){
    cout <<"Veuillez utilisez un des paramètres suivants :\nhello\nrender\nrandom_ai\nplayer_vs_rai\nengine"<<
    "\nheuristic_ai\nplayer_vs_hai\nhai_vs_rai\nrollback\nplay\nthread\n"<<endl;
    //cout << "Veillez utiliser les commandes make unittest et make code-coverage depuis le dossier build" << endl;
}
