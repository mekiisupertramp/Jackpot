CC= gcc -Wall -std=gnu99
LIBS= -lpthread
testSignal: testSignal.o signal.o
	$(CC) $^ -o $@ $(LIBS)
	rm -rf *.o *.h.gch
testSignal.o: testSignal.c signal.h
	$(CC) -c $^ 
signal.o: signal.c signal.h
	$(CC) -c $^
clean:
	rm -rf *.o *.h.gch testSignal
