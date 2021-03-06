#include <iostream>
#include <functional>
#include <unistd.h>
#include "Command_Client_Engine.h"
#include "state.h"
#include "render.h"
#include "engine.h"

using namespace client;
using namespace render;
using namespace engine;
using namespace state;
using namespace std;


Command_Client_Engine::Command_Client_Engine() {
}
Command_Client_Engine::~Command_Client_Engine(){
}
void Command_Client_Engine::execute() {
    cout << "TEST ENGINE" << endl;
    Engine engine;
    engine.getState().setMode("engine");
    engine.getState().initPlayers();
    engine.getState().initCharacters();
    engine.getState().initMapCell();
    cout << " INIT DONE" << endl;

    sf::RenderWindow window(sf::VideoMode(32 * 26 + 500, 32 * 24), "Zorglub");
    StateLayer stateLayer(engine.getState(), window);
    stateLayer.initTextureArea(engine.getState());

    StateLayer *ptr_stateLayer = &stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);

    bool booting = true;
    bool firstround = true;
    bool secondroun = false;
    bool thirdround = false;
    bool fourround = false;
    bool fiveround = false;
    bool sixround = false;
    int p1X;
    int p1Y;
    int p2X;
    int p2Y;
    int priority;

    // hard code health bc its loong either wise
    engine.getState().getListCharacters(0)[0]->setNewHealth(25);
    engine.getState().getListCharacters(0)[0]->setPrecision(15, 15, 15, 15);// precision to 1
    engine.getState().getListCharacters(0)[0]->setDodge(8, 8);// set dodge to 0

    engine.getState().getListCharacters(1)[0]->setNewHealth(25);
    engine.getState().getListCharacters(1)[0]->setPrecision(15, 15, 15, 15);// precision to 1
    engine.getState().getListCharacters(1)[0]->setDodge(8, 8);// set dodge to 0
    engine.getState().getListCharacters(1)[0]->getCharWeap()->setTypeCapab(TELEPORT); // Teleport Capacity


    while (window.isOpen()) {
        sf::Event event;
        if (booting) {
            stateLayer.draw(window);
            booting = false;
        }
        while (1) {
            if (firstround) {
                p1X = engine.getState().getListCharacters(0)[0]->getPosition().getX();
                p1Y = engine.getState().getListCharacters(0)[0]->getPosition().getY();

                int priority = 0;

                cout << "[Player 1] Character pos( " << engine.getState().getListCharacters(0)[0]->getPosition().getX()
                     << " " << engine.getState().getListCharacters(0)[0]->getPosition().getY() << endl;

                unique_ptr <engine::Command> ptr_sc(
                        new engine::Sel_Char_Command(*engine.getState().getListCharacters(0)[0]));
                engine.addCommand(move(ptr_sc), priority++);
                //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;


                engine.getState().setCurAction(MOVING); // hard change the sate cur action
                Position pos1{p1X, ++p1Y};
                unique_ptr <engine::Command> ptr_mc1(
                        new engine::Move_Command(*engine.getState().getListCharacters(0)[0], pos1));
                engine.addCommand(move(ptr_mc1), priority++);
                cout << "MOVE FROM pos(" << p1X << "," << p1Y << ")" << " TO " << "(" << p1X << "," << p1Y + 1 << ")"
                     << endl;
                if (engine.getState().getListCharacters(0)[0]->getMovementLeft() == 0) {

                    engine.getState().setCurAction(ATTACKING); // Hard set Attacking mode
                    cout << "STATE IN ATTACING MODE: SHOW ATTACK RANGE" << endl;
                    unique_ptr <engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                    engine.addCommand(move(ptr_ftc), priority++);
                    cout << "FINISHING TURN" << endl;
                    firstround = false;
                    secondroun = true;
                }
                engine.update();
            }
            if (secondroun) {
                engine.getState().setCurAction(IDLE);
                //Player 2
                p2X = engine.getState().getListCharacters(1)[0]->getPosition().getX();
                p2Y = engine.getState().getListCharacters(1)[0]->getPosition().getY();
                priority = 0;

                cout << "[Player 2] Character pos( " << engine.getState().getListCharacters(1)[0]->getPosition().getX()
                     << " " << engine.getState().getListCharacters(1)[0]->getPosition().getY() << endl;

                unique_ptr <engine::Command> ptr_sc(
                        new engine::Sel_Char_Command(*engine.getState().getListCharacters(1)[0]));
                engine.addCommand(move(ptr_sc), priority++);
                //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;


                engine.getState().setCurAction(MOVING); // hard change the sate cur action
                Position pos1{p2X, --p2Y};
                unique_ptr <engine::Command> ptr_mc2(
                        new engine::Move_Command(*engine.getState().getListCharacters(1)[0], pos1));
                engine.addCommand(move(ptr_mc2), priority++);
                cout << "MOVE FROM pos(" << p2X << "," << p2Y << ")" << " TO " << "(" << p2X << "," << p2Y + 1 << ")"
                     << endl;
                if (engine.getState().getListCharacters(1)[0]->getMovementLeft() == 0) {

                    engine.getState().setCurAction(ATTACKING);// Show the attack range
                    cout << "STATE IN ATTACING MODE: SHOW ATTACK RANGE" << endl;
                    unique_ptr <engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                    engine.addCommand(move(ptr_ftc), priority++);
                    cout << "FINISHING TURN" << endl;
                    secondroun = false;
                    thirdround = true;

                }
                engine.update();


            }
            if (thirdround) {
                engine.getState().setCurAction(IDLE);
                p1X = engine.getState().getListCharacters(0)[0]->getPosition().getX();
                p1Y = engine.getState().getListCharacters(0)[0]->getPosition().getY();

                int priority = 0;

                cout << "[Player 1] Character pos( " << engine.getState().getListCharacters(0)[0]->getPosition().getX()
                     << " " << engine.getState().getListCharacters(0)[0]->getPosition().getY() << endl;

                unique_ptr <engine::Command> ptr_sc(
                        new engine::Sel_Char_Command(*engine.getState().getListCharacters(0)[0]));
                engine.addCommand(move(ptr_sc), priority++);
                //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;


                engine.getState().setCurAction(MOVING); // hard change the sate cur action
                Position pos1{p1X, ++p1Y};
                unique_ptr <engine::Command> ptr_mc1(
                        new engine::Move_Command(*engine.getState().getListCharacters(0)[0], pos1));
                engine.addCommand(move(ptr_mc1), priority++);
                cout << "MOVE FROM pos(" << p1X << "," << p1Y << ")" << " TO " << "(" << p1X << "," << p1Y + 1 << ")"
                     << endl;
                if (engine.getState().getListCharacters(0)[0]->getMovementLeft() == 0) {

                    engine.getState().setCurAction(ATTACKING); // Hard set Attacking mode
                    cout << "STATE IN ATTACING MODE: SHOW ATTACK RANGE" << endl;
                    unique_ptr <engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                    engine.addCommand(move(ptr_ftc), priority++);
                    cout << "FINISHING TURN" << endl;
                    thirdround = false;
                    fourround = true;
                }
                engine.update();

            }

            if (fourround) {
                engine.getState().setCurAction(IDLE);
                //Player 2
                p2X = engine.getState().getListCharacters(1)[0]->getPosition().getX();
                p2Y = engine.getState().getListCharacters(1)[0]->getPosition().getY();
                priority = 0;

                cout << "[Player 2] Character pos( " << engine.getState().getListCharacters(1)[0]->getPosition().getX()
                     << " " << engine.getState().getListCharacters(1)[0]->getPosition().getY() << endl;

                unique_ptr <engine::Command> ptr_sc(
                        new engine::Sel_Char_Command(*engine.getState().getListCharacters(1)[0]));
                engine.addCommand(move(ptr_sc), priority++);
                //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;


                engine.getState().setCurAction(MOVING); // hard change the sate cur action
                Position pos1{p2X, --p2Y};
                unique_ptr <engine::Command> ptr_mc2(
                        new engine::Move_Command(*engine.getState().getListCharacters(1)[0], pos1));
                engine.addCommand(move(ptr_mc2), priority++);
                cout << "MOVE FROM pos(" << p2X << "," << p2Y << ")" << " TO " << "(" << p2X << "," << p2Y + 1 << ")"
                     << endl;
                if (engine.getState().getListCharacters(1)[0]->getMovementLeft() == 3) { // has reach attack range
                    // ==3 because the update isn't done yet

                    engine.getState().setCurAction(ATTACKING);// Show the attack range
                    cout << "STATE IN ATTACING MODE: SHOW ATTACK RANGE" << endl;

                    unique_ptr <engine::Command> ptr_ac2(
                            new engine::Attack_Command(*engine.getState().getListCharacters(1)[0],
                                                       *engine.getState().getListCharacters(0)[0]));
                    engine.addCommand(move(ptr_ac2), priority++);
                    cout << "ATTACKED";


                    unique_ptr <engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                    engine.addCommand(move(ptr_ftc), priority++);
                    cout << "FINISHING TURN" << endl;
                    fourround = false;
                    fiveround = true;

                }
                engine.update();

            }
            if (fiveround) {
                engine.getState().setCurAction(IDLE);
                p1X = engine.getState().getListCharacters(0)[0]->getPosition().getX();
                p1Y = engine.getState().getListCharacters(0)[0]->getPosition().getY();

                int priority = 0;

                cout << "[Player 1] Character pos( " << engine.getState().getListCharacters(0)[0]->getPosition().getX()
                     << " " << engine.getState().getListCharacters(0)[0]->getPosition().getY() << endl;

                unique_ptr <engine::Command> ptr_sc(
                        new engine::Sel_Char_Command(*engine.getState().getListCharacters(0)[0]));
                engine.addCommand(move(ptr_sc), priority++);
                //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;

                engine.getState().setCurAction(ATTACKING);// Show the attack range
                cout << "STATE IN ATTACING MODE: SHOW ATTACK RANGE" << endl;
                unique_ptr <engine::Command> ptr_ac1(
                        new engine::Attack_Command(*engine.getState().getListCharacters(0)[0],
                                                   *engine.getState().getListCharacters(1)[0]));
                engine.addCommand(move(ptr_ac1), priority++);
                cout << "ATTACKED";

                unique_ptr <engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                engine.addCommand(move(ptr_ftc), priority++);
                cout << "FINISHING TURN" << endl;
                fiveround = false;
                sixround = true;
                engine.update();
            }
            if (sixround) {
                engine.getState().setCurAction(IDLE);
                //Player 2
                p2X = engine.getState().getListCharacters(1)[0]->getPosition().getX();
                p2Y = engine.getState().getListCharacters(1)[0]->getPosition().getY();
                priority = 0;

                cout << "[Player 2] Character pos( " << engine.getState().getListCharacters(1)[0]->getPosition().getX()
                     << " " << engine.getState().getListCharacters(1)[0]->getPosition().getY() << endl;

                unique_ptr <engine::Command> ptr_sc(
                        new engine::Sel_Char_Command(*engine.getState().getListCharacters(1)[0]));
                engine.addCommand(move(ptr_sc), priority++);
                //cout<< "The First Plyaer Character has been Selected: Sel_Char_Command"<<endl;

                Position posTeleport{p2X - 2, p2Y - 2};
                unique_ptr <engine::Command> ptr_cap(
                        new engine::Capab_Command(*engine.getState().getListCharacters(1)[0],
                                                  *engine.getState().getListCharacters(0)[0], posTeleport));
                engine.addCommand(move(ptr_cap), priority++);
                cout << "TELEPORTING" << endl;
                usleep(1000000);

                engine.getState().setCurAction(ATTACKING);// Show the attack range
                cout << "STATE IN ATTACING MODE: SHOW ATTACK RANGE" << endl;

                unique_ptr <engine::Command> ptr_ac2(
                        new engine::Attack_Command(*engine.getState().getListCharacters(1)[0],
                                                   *engine.getState().getListCharacters(0)[0]));
                engine.addCommand(move(ptr_ac2), priority++);
                cout << "ATTACKED";

                unique_ptr <engine::Command> ptr_ftc(new engine::Finish_Turn_Command());
                engine.addCommand(move(ptr_ftc), priority++);
                cout << "FINISHING TURN" << endl;
                sixround = false;
                engine.update();
            }


            window.pollEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();


        }

    }
}