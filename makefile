
CFLAGS= -I.
CC=g++

%.o: %.c
	$(CC) -lm -c -o $@ $< $(CFLAGS) 

armake: arithmetics.o -lm
	$(CC) -pthread -o arithmeticsTest arithmetics.o -lm


