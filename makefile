test: main.cpp Field.cpp Platform.cpp Player.cpp
	g++ main.cpp Field.cpp Platform.cpp Player.cpp -lncurses -lpthread -o test

