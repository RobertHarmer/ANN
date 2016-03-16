CC=gcc

all: nn.o
	$(CC) -o nn nn.o

nn.o: nn.c
	$(CC) -c nn.c


clean:
	sudo rm nn *.o
