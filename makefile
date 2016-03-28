CC=gcc

all: nn.o dllist.o
	$(CC) -o nn nn.o dllist.o -lm -g

nn.o: nn.c nn.h
	$(CC) -c nn.c -g

dllist.o: dllist.c
	$(CC) -c dllist.c -g

clean:
	sudo rm nn *.o
