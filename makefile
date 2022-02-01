CC = gcc
CLFAGS = -Wall
OBJ = ropeGame
SOURCE = main.c actors.c

all:
	$(CC) $(CLFAGS) -o $(OBJ) $(SOURCE)

exec:
	./$(OBJ)
clean:
	rm -rf $(OBJ)