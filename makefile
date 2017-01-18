CC = gcc -Wall -std=gnu99 -c -lm -lpthread -lrt -g

all: jackpot.o
	gcc $^ -o jackpot -lm -lpthread

jackpot.o: main.c
	$(CC) $^ -o jackpot.o

wheel.o: wheel.c wheel.h
	$(CC) $^

clean:
	rm -f *.o jackpot
	rm -rf Libs/*.gch