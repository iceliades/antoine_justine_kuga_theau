#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace state;

State::State():cursor(10,10,3){ // call a specific constructor
    round=1;
    endGame=false;
    curPlayerID=1;
    nbOfPlayers=2;
    curAction=IDLE;
    gameWinner=0;

}
State::~State(){}

//getters
void State::initPlayers(){
    // for now 2 Players
    unique_ptr<Player> ptrPlayer1(new Player(1));
    unique_ptr<Player> ptrPlayer2(new Player(2));
    listPlayers.push_back(move(ptrPlayer1));
    listPlayers.push_back(move(ptrPlayer2));

}

void State::initMapCell(){

    int nbWidthTile= 26;
    int nbHeightTile=24;
    std::string path;
    if( mode=="test")
        path="../../../res/textures/map.csv";
    else
        path="res/textures/map.csv";

    std::ifstream file(path,ios::in);
 
    
    std::string content, line, tile_code;
    int map_tile_code[nbWidthTile*nbHeightTile]; // width*height

        // Read the file by storing all the data into one string -> content

    if (file){
        while (std::getline(file,line)){
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
    for (int i=0; i<nbHeightTile;i++){
        std::vector<std::unique_ptr<MapCell>> mapLine;
        for(int j=0;j<nbWidthTile;j++){
            
            if(map_tile_code[k]<9){ // In the map tileset only the first nine tiles are not obstacles
                std::unique_ptr<MapCell> ptr_space (new SpaceMapTiles(Sand,j,i,map_tile_code[k]));
                mapLine.push_back(move(ptr_space)); 

            }else{

                std::unique_ptr<MapCell> ptr_obstacle(new ObstacleMapTiles(Rock,j,i,map_tile_code[k]));
                mapLine.push_back(move(ptr_obstacle));
            }
            k++;
        }
        map.push_back(move(mapLine));
    }

}

void State::initCharacters(){


    if (mode=="engine"){
        unique_ptr<Character> eptrCrook1(new Character(CROOK,"CROOK1",4,2,0));
        unique_ptr<Character> eptrKnight2(new Character(KNIGHT,"KNIGHT2",4,22,42));
        listPlayers[0]->getListCharacters().push_back(move(eptrCrook1));
        listPlayers[1]->getListCharacters().push_back(move(eptrKnight2));

    }else
    {
            //init Player 1 Characters
        unique_ptr<Character> ptrCrook1(new Character(CROOK,"CROOK1",2,10,0));
        unique_ptr<Character> ptrKnight1(new Character(KNIGHT,"KNIGHT1",2,12,28));
        unique_ptr<Character> ptrDwarf1(new Character(DWARF,"DWARF1",2,14,56));
        // testing for render
        if (mode=="render")
            ptrCrook1->setStatus(SELECTED);
        listPlayers[0]->getListCharacters().push_back(move(ptrCrook1));
        listPlayers[0]->getListCharacters().push_back(move(ptrKnight1));
        listPlayers[0]->getListCharacters().push_back(move(ptrDwarf1));

        //init Player 2 Characters
        unique_ptr<Character> ptrCrook2(new Character(CROOK,"CROOK2",23,10,0));
        unique_ptr<Character> ptrKnight2(new Character(KNIGHT,"KNIGHT2",23,12,15));
        unique_ptr<Character> ptrDwarf2(new Character(DWARF,"DWARF2",23,14,56));
        listPlayers[1]->getListCharacters().push_back(move(ptrCrook2));
        listPlayers[1]->getListCharacters().push_back(move(ptrKnight2));
        listPlayers[1]->getListCharacters().push_back(move(ptrDwarf2));
        
    }
    

   // set Index for Characets for each Players
    for(unsigned int i=0; i<listPlayers.size();i++){
        for (unsigned int j=0; j<listPlayers[i]->getListCharacters().size();j++){
            //Stats charStats= listPlayers[i]->getListCharacters()[j]->getStats();       
            
            // Not a very clean code 
            // Init can take parameters for 
            listPlayers[i]->getListCharacters()[j]->setIndex(j);
            listPlayers[i]->getListCharacters()[j]->setPlayerID(i+1);
            //listPlayers[i]->getListCharacters()[j]->setHealth(charStats.getStamina(),charStats.getStrength());
        }           
    }
    cursor.setPosition(listPlayers[0]->getListCharacters()[0]->getPosition());
}



// A character has been selected
bool State::ifStelected(){
    for(unsigned int i=0;i<listPlayers.size();i++){
        for(unsigned int j=0;j<listPlayers[i]->getListCharacters().size();j++){
            if(listPlayers[i]->getListCharacters()[j]->getStatus() == SELECTED)
                return true;
        }
    }
    return false;
}

CopyState State::save(){

    State* s = new State();
    s->initPlayers();
    //copyState.recover()= new State();
    
    // save Character
    for(unsigned int i=0; i<listPlayers.size();i++){
        for(unsigned int j=0; j<this->getListCharacters(i).size();j++){
            unique_ptr<Character> newChar(new Character(*this->getListCharacters(i)[j]->clone()));
            s->getListCharacters(i).push_back(move(newChar));
        }
    }

    // save map
    for(auto& line : this->getMap()){
        vector<unique_ptr<MapCell>> clonedLine;
        for(auto& cell : line){
            if(cell->isSpace()){
                SpaceMapTiles* smc = ((SpaceMapTiles*)cell.get())->clone();
                unique_ptr<MapCell> upmc(new SpaceMapTiles(*smc));
                clonedLine.push_back(move(upmc));
            } else {
                ObstacleMapTiles* omc = ((ObstacleMapTiles*)cell.get())->clone();
                unique_ptr<MapCell> upmc(new ObstacleMapTiles(*omc));
                clonedLine.push_back(move(upmc));
            }
        }
        s->getMap().push_back(move(clonedLine));
    }

    

    s->getCursor().setPosition(this->getCursor().getPosition());
    s->getCursor().setTileCode(this->getCursor().getTileCode());
    s->getCursor().setVisible(this->getCursor().getVisible());
    s->setCurAction(this->getCurAction());
    s->setEndGame(this->getEndGame());
    s->setMode(this->getMode());
    s->setRound(this->getRound());
    s->setCurPlayerID(this->getCurPlayerID());
    s->setGameWinner(this->getGameWinner());
    
    for (size_t i = 0; i < observers.size(); i++)
    {
        s->registerObserver(observers[i]);
    }
    CopyState cs{*s};
    return cs;

}



void State::load(CopyState& copyState){
    
    // characters
    if(listPlayers[0]->getListCharacters().empty()==0){
        listPlayers[0]->getListCharacters().clear();
    }
    if(listPlayers[1]->getListCharacters().empty()==0){
        listPlayers[1]->getListCharacters().clear();
    }

    for(unsigned int i=0; i<copyState.recover().getListPlayers().size();i++){
        for(unsigned int j=0; j<copyState.recover().getListCharacters(0).size();j++){
            unique_ptr<Character> newChar(new Character(*copyState.recover().getListCharacters(i)[j]->clone()));
            Weapon *w = new Weapon(newChar->getCharWeap()->getTypeWeapon());
            w->setDammages(newChar->getCharWeap()->getDammages());
            newChar->setCharWeap(w);  
            listPlayers[i]->getListCharacters().push_back(move(newChar));
        }
    }
    // curState clear map
    if(getMap().empty()==0){
        this->getMap().clear();
        }
    for(auto& line : copyState.recover().getMap()){
        vector<unique_ptr<MapCell>> clonedLine;
        for(auto& cell : line){
            if(cell->isSpace()){
                SpaceMapTiles* smc = ((SpaceMapTiles*)cell.get())->clone();
                unique_ptr<MapCell> upmc(new SpaceMapTiles(*smc));
                clonedLine.push_back(move(upmc));
            } else {
                ObstacleMapTiles* omc = ((ObstacleMapTiles*)cell.get())->clone();
                unique_ptr<MapCell> upmc(new ObstacleMapTiles(*omc));
                clonedLine.push_back(move(upmc));
            }
        }
        this->getMap().push_back(move(clonedLine));
    }
  
    this->setCurAction(copyState.recover().getCurAction());
    this->getCursor().setPosition(copyState.recover().getCursor().getPosition());
    this->getCursor().setTileCode(copyState.recover().getCursor().getTileCode());
    this->getCursor().setVisible(copyState.recover().getCursor().getVisible());
    this->setEndGame(copyState.recover().getEndGame());
    this->setMode(copyState.recover().getMode());
    this->setRound(copyState.recover().getRound());
    this->setCurPlayerID(copyState.recover().getCurPlayerID());
    this->setGameWinner(copyState.recover().getGameWinner());

}


// setters and getters

void State::setRound(int newRound){ round= newRound;}
void State::setEndGame(bool res){ endGame=res;}
void State::setCurPlayerID(int newPlayer){curPlayerID=newPlayer;}
void State::setCurAction(CurActionID newAction){curAction=newAction;}
void State::setGameWinner(int winnerID){ gameWinner=winnerID;}
void State::setMode(std::string newMode){ mode= newMode;}


bool State::getEndGame(){ return endGame;}
int State::getRound(){ return round;}
int State::getCurPlayerID(){ return curPlayerID;}
int State::getNbOfPlayers(){ return nbOfPlayers;}
int State::getGameWinner(){ return gameWinner;}
std::string State::getMode(){ return mode;}

Cursor& State::getCursor(){ return cursor;}
CurActionID State::getCurAction(){return curAction;}
std::vector<std::unique_ptr<Player>>& State::getListPlayers (){
    return listPlayers;
}
std::vector<std::unique_ptr<Character>>& State::getListCharacters (int playerID){
    return listPlayers[playerID]->getListCharacters();
}

std::vector<std::vector<std::unique_ptr<MapCell>>>& State::getMap (){
      return map;
  }













