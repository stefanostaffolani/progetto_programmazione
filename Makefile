test: main.cpp Platform.o Field.o Player.o Bonus.o Item.o Shoot.o Enemy.o
	g++ -o test main.cpp Platform.o Field.o Bonus.o Item.o Player.o Shoot.o Enemy.o -lncurses -lpthread

Item.o: Item.cpp Item.hpp
	g++ -c Item.cpp

Platform.o: Platform.cpp Platform.hpp
	g++ -c Platform.cpp

Player.o: Player.cpp Player.hpp
	g++ -c Player.cpp

Bonus.o: Bonus.cpp Bonus.hpp
	g++ -c Bonus.cpp

Field.o: Field.cpp Field.hpp
	g++ -c Field.cpp

Shoot.o: Shoot.cpp Shoot.hpp
	g++ -c Shoot.cpp

Enemy.o: Enemy.cpp Enemy.hpp
	g++ -c Enemy.cpp

clean:
	rm *.o test
