CC=gcc

all: nn.o dllist.o
	$(CC) -o nn nn.o dllist.o -lm

nn.o: nn.c nn.h
	$(CC) -c nn.c

dllist.o: dllist.c
	$(CC) -c dllist.c

clean:
	sudo rm nn *.o
