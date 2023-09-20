p1_6: p.o f.o
	gcc -Wall -g f.o p.o -lm -o p1_6

p.o: p.c Header.h
	gcc -c -Wall p.c

f.o: f.c Header.h
	gcc -c -Wall f.c

.PHONY: clean
clean:
	rm -f *.o
	rm p1_6
