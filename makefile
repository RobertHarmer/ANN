CC=gcc

all: nn.o
	$(CC) -o nn nn.o -lm

nn.o: nn.c
	$(CC) -c nn.c -lm


clean:
	sudo rm nn *.o
