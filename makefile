CC = gcc -Wall -std=gnu99 -c

all: jackpot.o wheels.o display.o timing.o
	gcc $^ -o jackpot -lpthread

jackpot.o: main.c
	$(CC) $< -o jackpot.o

wheels.o: libs/wheels.c
	$(CC) $<
	
display.o: libs/display.c
	$(CC) $<

timing.o: libs/timing.c
	$(CC) $<

clean:
	rm -f *.o jackpot
