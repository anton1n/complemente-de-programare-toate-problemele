all: server client

server: server.o
	gcc -Wall server.o -lm -o server

server.o: server.c
	gcc -c -Wall server.c

client: client.o
	gcc -Wall client.c -lm -o client

client.o: client.c
	gcc -c -Wall client.c

.PHONY: clean
clean:
	rm -f *.o
	rm client
	rm server