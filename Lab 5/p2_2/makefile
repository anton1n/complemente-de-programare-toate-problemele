all: p0 p1 p2

p0: p0.o
	gcc -Wall -g p0.o -lm -o p0

p0.o: p0.c
	gcc -c -Wall p0.c 

p1: p1.o
	gcc -Wall -g p1.o -lm -o p1

p1.o: p1.c
	gcc -c -Wall p1.c 

p2: p2.o
	gcc -Wall -g p2.o -lm -o p2

p2.o: p2.c
	gcc -c -Wall p2.c

.PHONY: clean
clean:
	rm -f *.o
	rm p0
	rm p1
	rm p2
	rm fifo
