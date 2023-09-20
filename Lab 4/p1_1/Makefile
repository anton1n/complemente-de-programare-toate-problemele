CC = gcc
CFLAGS = -Wall -pthread

p1_1: p1_1.o
	$(CC) $(CFLAGS) p1_1.o -o p1_1

p1_1.o: p1_1.c
	$(CC) $(CFLAGS) -c p1_1.c

.PHONY: clean
clean:
	rm -f *.o
	rm -f p1_1
