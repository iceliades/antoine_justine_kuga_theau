#include <iostream>
#include <unistd.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>


using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
    if(argc==2) {
        
        if (string(argv[1]) == "hello")cout << "Bonjour le monde!" << endl;
        
        else if (string(argv[1]) == "state") {
            cout << "Veillez utiliser les commandes make unittest et make code-coverage depuis le dossier build" << endl;
    
        }

    }
    return 0;
}
