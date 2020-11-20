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
#include <iostream>
#include <sstream>

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
    if(argc==2) {
        
        if (string(argv[1]) == "hello")cout << "Bonjour le monde!" << endl;
        
        else if (string(argv[1]) == "state") {
            cout << "Veillez utiliser les commandes make unittest et make code-coverage depuis le dossier build" << endl;
    
        }else if (string(argv[1]) == "render")
        {
            State state;
            state.initPlayers();
            state.initCharacters();
            state.initMapCell();
            
            sf::RenderWindow window(sf::VideoMode(32*26,32*24), "Zorglub");
            StateLayer stateLayer (state,window);
            
            
            stateLayer.initTextureArea(state);
            while (window.isOpen()){
                sf::Event event;
                 while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                    window.close();
                    }
                }
                stateLayer.draw(window);
                usleep(50000);
            
                
            }

        }
        

    }
    return 0;
}
