p0 : operatii.o p0.o
	gcc -Wall -g operatii.o p0.o -lm -o p0

p0.o: p0.c operatii.h
	gcc -c -Wall p0.c
operatii.o: operatii.c operatii.h
	gcc -c -Wall operatii.c

.PHONY:clean
clean:
	del -f *.o
	del p0.exe
