#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace state;

State::State():cursor(10,10,2){ // call a specific constructor
    round=1;
    endGame=false;
    curPlayerID=1;
    nbOfPlayers=1;

}
State::~State(){}

//getters
void State::initPlayers(){
    unique_ptr<Player> ptrPlayer1(new Player(1));
    unique_ptr<Character> ptrCrook(new Character(CROOK,"crook",10,10,24));
    ptrPlayer1->getListCharacters().push_back(move(ptrCrook));

    listPlayers.push_back(move(ptrPlayer1));


}

  std::vector<std::vector<std::unique_ptr<MapCell>>>& State::getMap (){
      return map;
  }

  void State::initMapCell(){

    std::ifstream file("res/Images/map.csv",ios::in);
    std::string content, line, tile_code;
    int map_tile_code[50*25]; // width*height

        // Read the file by storing all the data into one string -> content
    if (file){
        while (getline(file,line)){
            line = line + ",";
            content = content + line;
        }
        file.close();
    }
     std::stringstream contentStream(content); 
    int i=0;
    
    while(std::getline(contentStream, tile_code, ',')){ // ',' is a delimiter of a line
        // Convert string tile codes into integers and store it in an array
        map_tile_code[i] = (int) std::stoi(tile_code);
        i++;
    }

    int k=0;
    for (int i=0; i<25;i++){
        std::vector<std::unique_ptr<MapCell>> mapLine;
        for(int j=0;j<50;j++){
            int var=map_tile_code[k];
            
            if(var<9){ // In the map tileset only the first nine tiles are not obstacles
                std::unique_ptr<MapCell> ptr_space (new SpaceMapTiles(Sand,j,i,var));
                mapLine.push_back(move(ptr_space)); 

            }else{

                std::unique_ptr<MapCell> ptr_obstacle(new ObstacleMapTiles(Rock,j,i,var));
                mapLine.push_back(move(ptr_obstacle));
            }
            k++;
        }
        map.push_back(move(mapLine));
    }




  }