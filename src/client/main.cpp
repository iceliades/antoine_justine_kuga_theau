#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include "../../test/shared/test_shared_state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
    if(argc>1) {
        if (string(argv[1]) == "hello")cout << "Bonjour le monde!" << endl;
        else if (string(argv[1]) == "state") {
            state::test_shared_state();
        }

    }
    return 0;
}
