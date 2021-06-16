test: main.cpp Platform.o Field.o Player.o
	g++ -o test main.cpp Platform.o Field.o Player.o -lncurses -lpthread

Platform.o: Platform.cpp Platform.hpp
	g++ -c Platform.cpp

Player.o: Player.cpp Player.hpp
	g++ -c Player.cpp


Field.o: Field.cpp Field.hpp
	g++ -c Field.cpp

clean:
	rm *.o test
