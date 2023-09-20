p1_5: p.o f.o
	gcc -g -Wall p.o f.o -lm -o p1_5

p.o: p.c Header.h
	gcc -c -Wall p.c 

f.o: f.c Header.h
	gcc -c -Wall f.c

.PHONY: clean
clean:
	rm -f *.o
	rm p1_5

