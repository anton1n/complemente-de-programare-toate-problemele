p1_5: p.o f.o 
	gcc -g -Wall p.o -lm -o p1_5

p.o: p.c Header.h
	gcc -c -Wall p.c 

.PHONY: clean
clean:
	rm -f *.o
	rm p1_5

