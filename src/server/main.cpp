#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Pour compter une minute d'enregistrement
#include <fstream> // Pour la gestion des fichiers

#include "state.h"
#include "engine.h"
#include "ai.h"
#include "server.h"

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;
using namespace server;




int main(int argc, char const *argv[])
{
    if (argc > 1){   
        // Test pour un Hello
        if (strcmp(argv[1], "Hello") == 0)
            cout << "Bonjour " << endl;

        else if (strcmp(argv[1], "record") == 0){

            std::string commands_file = "res/record/replay.txt";

            engine::Engine myEngine;

            myEngine.setEnableRecord(true);
            myEngine.getState().initPlayers();
            myEngine.getState().initCharacters();
            myEngine.getState().initMapCell();

            ai::HeuristicAI AI_1(myEngine, 1);
            ai::HeuristicAI AI_2(myEngine, 2);

            cout << "<<< Record >>>" << endl;

            cout << "HAi vs HAI" << commands_file << endl;
            sleep(2);
            cout << "<<< Début de l'enregistrement >>>" << endl;

            // On joue une minute de jeu
            clock_t time;
            while (time=clock()/CLOCKS_PER_SEC <=60){
                // joueur1
                if(myEngine.getState().getEndGame())
                    break;
                if (myEngine.getState().getRound() % 2 != 0)
                {
                    AI_1.run(myEngine);
                }
                // joueur2
                else
                {
                    AI_2.run(myEngine);
                }
            }
            cout << "<<< Fin de l'enregistrement >>>" << endl;

            cout << "<<< ###############################################################" << endl;
            cout << " ENREGISTREMENT DANS LE FICHIER REPLAY.TXT "<<endl;
            cout << "<<< ###############################################################" << endl;
            // Ouverture du fichier en ecriture en effacant son contenu à l'ouverture
            std::ofstream written_file(commands_file, ios::out | ios::trunc);
            if (written_file){

                Json::Value record = myEngine.getRecord();
                cout << record << endl;

                // Ecriture dans le fichier du tableau de commandes de cette partie
                written_file << record;

                // Fermeture du fichier
                written_file.close();


            }
            else{
                cerr << "Impossible d'ouvrir le fichier pour l'ecriture" << endl;
            }
        }
        else if (strcmp(argv[1], "listen") == 0){
            
            try{
                server::Game game;
            
                std::unique_ptr<AbstractService> ptr_versionService(new VersionService());

                std::unique_ptr<AbstractService> ptr_playerService(new PlayerService(ref(game)));
                
                cout << "server is listening in port 80..." << endl << "press button to stop the server" << endl;
                //(void)getc(stdin);
                
            }
            catch (exception &e)
            {
                cerr << "Exception: " << e.what() << endl;
            }


        }


        
    }
}