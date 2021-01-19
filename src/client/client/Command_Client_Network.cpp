#include "Command_Client_Network.h"
#include <iostream>
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include "client.h"
#include <SFML/Network.hpp>

using namespace client;
using namespace engine;
using namespace render;
using namespace state;
using namespace std;

Command_Client_Network::Command_Client_Network() {}

Command_Client_Network::~Command_Client_Network() {}

void Command_Client_Network::execute() {

    string name;
    cout << "Enter your name: ";
    cin >> name;
    while (name.length() < 3 || name.length() > 15) {
        cout << "Invalid name. At least 3 characters and up to 15. Re-enter: ";
        cin >> name;
    }

    sf::Http http("http://localhost/", 80);

    sf::Http::Request request1;
    request1.setMethod(sf::Http::Request::Post);
    request1.setUri("/player");
    request1.setHttpVersion(1, 0);

    Json::Value me;
    me["name"] = name;
    me["free"] = true;

    request1.setBody(me.toStyledString());

    sf::Http::Response response1 = http.sendRequest(request1);
    cout << "The body :" << response1.getBody() << endl;
    cout << "The status :" << response1.getStatus() << endl;
    Json::Reader jsonReader;
    Json::Value rep1 ="";
    if (jsonReader.parse(response1.getBody(), rep1)) {
        int idPlayer = rep1["id"].asInt();

        // query array of players in lobby.
        sf::Http::Request players0;
        players0.setMethod(sf::Http::Request::Get);
        players0.setUri("/player");
        players0.setHttpVersion(1, 0);
        sf::Http::Response playersResp0 = http.sendRequest(players0);
        Json::Reader jsonReaderPlayers0;
        Json::Value jsonPlayers0;
        jsonReaderPlayers0.parse(playersResp0.getBody(), jsonPlayers0);

        cout << "Hello " << name << "! You joined the lobby succesfully!" << endl;
        cout << "Your ID is: " << idPlayer << endl << endl;
        cout << "Players in the lobby: (" << jsonPlayers0["players"].size() << "/2)" << endl;

        for (auto &playerInLobby : jsonPlayers0["players"]) {
            cout << "\t-" << playerInLobby[1].asString() << " [id: " << playerInLobby[0].asString() << "]" << endl;
        }

        cout << "Press q to exit from the lobby" << endl;

        while (getchar() != 'q') {/*endless retry*/}

        sf::Http::Request request3;
        request3.setMethod(sf::Http::Request::Delete);
        string uri2 = "/player/" + to_string(idPlayer);
        request3.setUri(uri2);
        request3.setHttpVersion(1, 0);
        http.sendRequest(request3);
        cout << "Player " << idPlayer << " deleted" << endl;

        // query players in lobby again
        sf::Http::Request players;
        players.setMethod(sf::Http::Request::Get);
        players.setUri("/player");
        players.setHttpVersion(1, 0);
        sf::Http::Response playersResp = http.sendRequest(players);

        Json::Reader jsonReaderPlayers;
        Json::Value jsonPlayers;
        jsonReaderPlayers.parse(playersResp.getBody(), jsonPlayers);

        cout << "Players in the lobby: (" << jsonPlayers["players"].size() << "/2)" << endl;
        for (auto &playerStillInLobby : jsonPlayers["players"]) {
            cout << "\t-" << playerStillInLobby[1].asString() << " [id: " << playerStillInLobby[0].asString() << "]"
                 << endl;
        }
    } else {
        cout << "Out of places: 2/2 players in the lobby." << endl;
    }
}