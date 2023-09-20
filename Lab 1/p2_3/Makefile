p2_3 : f.o main.o
	gcc -Wall -g f.o main.o -lm -o p2_3

f.o: f.c Header.h
	gcc -c -Wall f.c
main.o: main.c Header.h
	gcc -c -Wall main.c

.PHONY:clean
clean:
	del -f *.o
	del pr3.exe
