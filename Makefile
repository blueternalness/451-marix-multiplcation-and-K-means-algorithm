CC = gcc

all: p1a p1b p2

p1a: p1a.c
	$(CC) -o p1a p1a.c

p1b: p1b.c
	$(CC) -o p1b p1b.c

p2: p2.c
	$(CC) -fopenmp -o p2 p2.c

clean:
	rm -f p1a p1b p2
