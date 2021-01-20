#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Pour compter une minute d'enregistrement
#include <fstream> // Pour la gestion des fichiers



#include <sstream>
#include <map>
#include <memory>

#include <microhttpd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/select.h>



#include "state.h"
#include "engine.h"
#include "ai.h"
#include "server.h"

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;
using namespace server;


class Request
        {
                public:
                struct MHD_PostProcessor *pp = nullptr;
                string data;
                ~Request()
                {
                    if (pp)
                        MHD_destroy_post_processor(pp);
                }
        };

static int post_iterator(void *cls,
                         enum MHD_ValueKind kind,
                         const char *key,
                         const char *filename,
                         const char *content_type,
                         const char *transfer_encoding,
                         const char *data, uint64_t off, size_t size)
{
    return MHD_NO;
}

static int handler(void *cls,
                   struct MHD_Connection *connection,
                   const char *url,
                   const char *method,
                   const char *version,
                   const char *upload_data, size_t *upload_data_size, void **ptr)
{
    Request *request = (Request *)*ptr;

    if (!request)
    {
        request = new Request();
        if (!request)
        {
            return MHD_NO;
        }
        *ptr = request;
        if (strcmp(method, MHD_HTTP_METHOD_POST) == 0 || strcmp(method, MHD_HTTP_METHOD_PUT) == 0)
        {
            request->pp = MHD_create_post_processor(connection, 1024, &post_iterator, request);
            if (!request->pp)
            {
                cerr << "Failed to setup post processor for " << url << endl;
                return MHD_NO;
            }
        }
        return MHD_YES;
    }

    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0 || strcmp(method, MHD_HTTP_METHOD_PUT) == 0)
    {
        MHD_post_process(request->pp, upload_data, *upload_data_size);
        if (*upload_data_size != 0)
        {
            request->data = upload_data;
            *upload_data_size = 0;
            return MHD_YES;
        }
    }

    HttpStatus status;
    string response;
    try
    {
        ServicesManager *manager = (ServicesManager *)cls;
        status = manager->queryService(response, request->data, url, method);
    }
    catch (ServiceException &e)
    {
        status = e.getStatus();
        response += "\n";
    }
    catch (exception &e)
    {
        status = HttpStatus::SERVER_ERROR;
        response = e.what();
        response += "\n";
    }
    catch (...)
    {
        status = HttpStatus::SERVER_ERROR;
        response = "Unknown exception\n";
    }

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response.size(), (void *)response.c_str(), MHD_RESPMEM_MUST_COPY);
    if (strcmp(method, MHD_HTTP_METHOD_GET) == 0)
    {
        MHD_add_response_header(mhd_response, "Content-Type", "application/json; charset=utf-8");
    }
    int ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

static void request_completed(void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe)
{
    Request *request = (Request *)*con_cls;
    if (request)
    {
        delete request;
        *con_cls = nullptr;
    }
}


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
            try
            {
                VersionService versionService;
                std::unique_ptr<AbstractService> ptr_versionService(new VersionService(versionService));

                ServicesManager servicesManager;
                servicesManager.registerService(move(ptr_versionService));

                Game game;

                PlayerService playerService(std::ref(game));
                std::unique_ptr<AbstractService> ptr_playerService(new PlayerService(playerService));

                servicesManager.registerService(move(ptr_playerService));

                struct MHD_Daemon *d;
                if (argc != 2)
                {
                    printf("%s PORT\n", argv[0]);
                    return 1;
                }
                int port_id = 80;
                d = MHD_start_daemon( // MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
                    MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                    // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
                    // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
                    port_id,
                    NULL, NULL,
                    &handler, (void *)&servicesManager,
                    MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                    MHD_OPTION_END);

                if (d == NULL)
                    return 1;
                cout << "server is listening in port " << port_id << endl << "press any button to stop the server" << endl;
                (void)getc(stdin);
                MHD_stop_daemon(d);
            }
            catch (exception &e)
            {
                cerr << "Exception: " << e.what() << endl;
            }
        }


        
    }
}