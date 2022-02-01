CC = gcc
CLFAGS = -Wall pkg-config allegro-5 allegro_font-5 --libs
OBJ = ropeGame
SOURCE = main.c

all:
	$(CC) $(CLFAGS) -o $(OBJ) $(SOURCE)

exec:
	./$(OBJ)
clean:
	rm -rf $(OBJ)