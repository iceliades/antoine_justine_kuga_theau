# Projet Logiciel Transversal : Zorglub

## Getting Started

This project's aim is to make a video game in C++ as a final assignment for all software class of "Informatique et Systèmes", a 3rd year specialisation in ENSEA.

## Zorglub Game Rules

This game is a 1 vs 1 game.  
Each player has a team which contains between 3 and 6 characters.  
Each character has attributes (which he can choose), skills (calculated automatically thanks to the attributes) and a weapon (close combat, distant combat, magic power).  
On each turn, the player has 2 action points (movement or attack).  
The object of the game is to be the last to survive.

### Depedencies to install
In order to get the game running  you will need to install some package on your Linux environment; in a terminal:

Git

```bash
sudo apt install git
```
Dia is the software used to create UML diagrams

```bash
sudo apt-get install dia
```
cmake and g++ are used to compile C++ code

```bash
sudo apt install cmake
sudo apt install g++
```
lcov and lcov are used to check the code coverage
```bash
sudo apt install lcov
sudo apt install gcovr
```
smfl libraries for the render
```bash
sudo apt-get install libsfml -dev
sudo apt-get install libboost-all-dev
```

## Build instructions
Then, in order to use our project, you have to clone it, this way:

```bash
git clone https://github.com/iceliades/antoine_justine_kuga_theau
cd antoine_justine_kuga_theau
mkdir build (first use only)
cd build
clean
cmake .. && make
(+ cmd in next chapters)
<<<<<<< HEAD
```

## 1.1 Development environment
The recommended environment to use and install this project is a linux distribution of your choosing. Preferably Ubuntu 16.04 and upwards.  
Hello World dislay
```bash
./bin/client hello
```
## 1.final Game state
Unit test
```bash
make unittest
=======
```

## 1.1 Development environment
The recommended environment to use and install this project is a linux distribution of your choosing. Preferably Ubuntu 16.04 and upwards.  
Hello World dislay
```bash
./bin/client hello
```
## 1.final Game state
Unit test
```bash
make unittest
```
## 2.1 Render
Render automatic display
```bash
./bin/client render
```

## 2.2 Engine
Engine automatic display
```bash
./bin/client engine
```
## 2. Random AI
Random AI vs Random AI
```bash
./bin/client random_ai
```
Player vs RandomAI
```bash
./bin/client player_vs_rai
```

## 3.1 Heuristic AI
Heuristic AI vs Heuristic AI
```bash
./bin/client heuristic_ai
```
Player vs Heuristic AI
```bash
./bin/client player_vs_hai
```
## 3.final Advanced AI

Command for record and save in the replay.txt
```bash
./bin/server record
```

Command to play the record 
```bash
./bin/client play
```

## 4.1 Multi threading

Threading with music and 2 Heuristic AIs dueling

```
./bin/client demo_thread_hai
>>>>>>> dev
```
## 2.1 Render
Render automatic display
```bash
./bin/client render
```

## 2.2 Engine
Engine automatic display
```bash
./bin/client engine
```
## 2. Random AI
Random AI vs Random AI 
```bash
./bin/client random_ai
```
Player vs RandomAI 
```bash
./bin/client player_vs_rai
```

## 3.1 Heuristic AI
Heuristic AI vs Heuristic AI 
```bash
./bin/client heuristic_ai
```
Player vs Heuristic AI
```bash
./bin/client player_vs_hai
```
## 3.final Advanced AI

## 4.1 Multi threading

## Report

Nothing to see here move along.

## Authors

* [Antoine](www.linkedin.com/in/antoine-montmaur-918936175)
* [Justine](www.linkedin.com/in/justine-charlet-0512 )
* [Kuga](https://github.com/Kuga23/)
* [Theau](https://github.com/iceliades/)