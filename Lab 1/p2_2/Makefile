p2_2 : f.o main.o
	gcc -Wall -g f.o main.o -lm -o p2_2

f.o: f.c Header.h
	gcc -c -Wall f.c
main.o: main.c Header.h
	gcc -c -Wall main.c

.PHONY:clean
clean:
	rm -f *.o
	rm p2_2
