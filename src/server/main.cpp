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

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;




int main(int argc, char const *argv[])
{
    if (argc > 1)
    {   
        // Test pour un Hello
        if (strcmp(argv[1], "Hello") == 0)
            cout << "Bonjour " << endl;

        else if (strcmp(argv[1], "record") == 0)
        {

            std::string commands_file = "replay.txt";

            engine::Engine engine{"monEnregistrementDeJeu"};

            engine.setEnableRecord(true);
            engine.getState().initMapCell();
            engine.getState().initCharacters();

            ai::HeuristicAI AI_1(engine, 1);
            ai::HeuristicAI AI_2(engine, 2);

            cout << "<<< Record >>>" << endl;

            cout << "On enregistre une minute de jeu (IA contre IA) dans le fichier " << commands_file << endl;
            cout << "On utilise deux IA heuristiques" << endl;
            sleep(2);

            cout << "<<< Début de l'enregistrement >>>" << endl;





            // On joue une minute de jeu
            clock_t time;
            while (time=clock()/CLOCKS_PER_SEC <=60){
                // joueur1
                if (engine.getState().getRound() % 2 != 0)
                {
                    AI_1.run(engine);
                }
                // joueur2
                else
                {
                    AI_2.run(engine);
                }
            }
            cout << "<<< Fin de l'enregistrement >>>" << endl;

            
            // Ouverture du fichier en ecriture en effacant son contenu à l'ouverture
            std::ofstream written_file(commands_file, ios::out | ios::trunc);
            if (written_file){

                Json::Value record = engine.getRecord();
                cout << record << endl;

                // Ecriture dans le fichier du tableau de commandes de cette partie
                written_file << record;

                // Fermeture du fichier
                written_file.close();


            }
            else{
                cerr << "Impossible d'ouvrir le fichier des commandes enregistrées pour l'ecriture" << endl;
            }
        }
    }