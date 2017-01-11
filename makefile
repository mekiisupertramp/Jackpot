CC = gcc -Wall -std=gnu99 -c -lm -lpthread -lrt -g
LIBS=-lSDL2

all: jackpot.o
	gcc $^ -o jackpot -lm -lpthread -lrt $(LIBS)

jackpot.o: main.c
	$(CC) $^ -o jackpot.o

clean:
	rm -f *.o gameoflife
	rm -rf Libs/*.gch