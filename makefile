CC = gcc -Wall -std=gnu99

all: jackpot.o wheels.o
	gcc $^ -o jackpot -lpthread

jackpot.o: main.c
	$(CC) $^ -o jackpot.o

wheels.o: Libs/wheels.c Libs/wheels.h
	$(CC) $^

clean:
	rm -f *.o jackpot
	rm -rf Libs/*.gch