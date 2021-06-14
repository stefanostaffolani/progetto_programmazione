test: main.cpp Field.cpp Platform.cpp Player.cpp Bonus.cpp
	g++ main.cpp Field.cpp Platform.cpp Player.cpp Bonus.cpp -lncurses -lpthread -o test

