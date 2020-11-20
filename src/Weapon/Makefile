
make : prog

prog: Weapon.o Main.o 
	g++ -o prog Weapon.o Main.o 
	
Main.o : Main.cpp Weapon.h
	g++ -Wall -c Main.cpp

Weapon.o : Weapon.cpp Weapon.h
	g++ -Wall -c Weapon.cpp


clean : 
	rm -f *.o
	rm -f prog

