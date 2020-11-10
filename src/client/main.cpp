#include <iostream>
#include <unistd.h>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
    if(argc>1) {
        if (strcmp(argv[1],"hello") == 0){
            cout<<"----------------------Test 'Hello World'-------------------------\n"<<endl;
            cout << "Bonjour le monde!\n" << endl;

            cout<<"----------------------Fin du test 'Hello World'-------------------------\n"<<endl;
        }
        else if (strcmp(argv[1],"state") == 0) {
            ;
        }

    }
    return 0;
}
