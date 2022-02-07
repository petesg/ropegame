CC = gcc
CLFAGS = -Wall -c
EFLAGS = # I don't know what this does?
EOPTION = `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`
SOURCE = main.c actors.c draw.c errors.c collision.c
EXC = ropeGame

all: $(EXC) $(SOURCE)

exec: $(EXC) $(SOURCE)
	./$(EXC)

clean:
	rm -rf $(EXC) *.o

$(EXC): 
	gcc $(SOURCE) $(EFLAGS) -o $(EXC) $(EOPTION)
