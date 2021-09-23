CC = g++ 
INCLUDES = -lncurses
DIR = ./src
OBJECTS = main.o Platform.o Field.o Player.o Bonus.o Item.o Shoot.o Enemy.o Enemies.o


test: $(OBJECTS)
	$(CC) -o test $(OBJECTS) $(INCLUDES)

main.o : $(DIR)/main.cpp
	$(CC) -c $(DIR)/main.cpp

Item.o: $(DIR)/Item.?pp
	$(CC) -c $(DIR)/Item.cpp

Platform.o: $(DIR)/Platform.?pp
	$(CC) -c $(DIR)/Platform.cpp

Player.o: $(DIR)/Player.?pp
	$(CC) -c $(DIR)/Player.cpp

Bonus.o: $(DIR)/Bonus.?pp
	$(CC) -c $(DIR)/Bonus.cpp

Field.o: $(DIR)/Field.?pp
	$(CC) -c $(DIR)/Field.cpp

Shoot.o: $(DIR)/Shoot.?pp
	$(CC) -c $(DIR)/Shoot.cpp

Enemy.o: $(DIR)/Enemy.?pp
	$(CC) -c $(DIR)/Enemy.cpp

Enemies.o: $(DIR)/Enemies.?pp
	$(CC) -c $(DIR)/Enemies.cpp

up:
	./test

clean:
	rm *.o test
