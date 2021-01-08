#include <iostream>
#include <unistd.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <render.h>
#include <engine.h>
#include <ai.h>
#include <client.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cstdio>
#include <functional>
#include <boost/function.hpp>

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace client;




int main(int argc,char* argv[])
{
    std::map<std::string,ICommand_Client*> MethodMap;

    MethodMap["hello"] = (ICommand_Client*)new Command_Client_Hello();
    MethodMap["render"] = (ICommand_Client*)new Command_Client_Render();
    MethodMap["random_ai"] = (ICommand_Client*)new Command_Client_RAI();
    MethodMap["player_vs_rai"] = (ICommand_Client*)new Command_Client_PAI();
    MethodMap["engine"] = (ICommand_Client*)new Command_Client_Engine();
    MethodMap["heuristic_ai"] = (ICommand_Client*)new Command_Client_HAI();
    MethodMap["player_vs_hai"] = (ICommand_Client*)new Command_Client_PHAI();
    MethodMap["hai_vs_rai"] = (ICommand_Client*)new Command_Client_RHAI();
    MethodMap["autre"] = (ICommand_Client*)new Command_Client_Autre();
    MethodMap["rollback"] = (ICommand_Client*)new Command_Client_Rollback();
    MethodMap["play"] = (ICommand_Client*)new Command_Client_Play();
    //MethodMap["deep_ai"] = (ICommand_Client*)new Command_Client_DeepAi();
    MethodMap["thread_hai"] = (ICommand_Client*)new Command_Client_Thread();



    if(argc==2) {
        if(MethodMap.find(argv[1])==MethodMap.end()) {
            MethodMap["autre"]->execute();
        }else {
            MethodMap[string(argv[1])]->execute();
        }
    }else{
        cout << "Give me something processable a.k.a hello/state/render/engine/random_ai/player_vs_rai/play" << endl;
    }

    if (argc<1){


        
    }
    return 0;
}
