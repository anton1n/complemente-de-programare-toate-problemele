all: server client

server: server.o SourceServer.o
	gcc -Wall server.o SourceServer.o -lm -o server

server.o: server.c HeaderServer.h
	gcc -Wall -c server.c

client: client.o SourceClient.o
	gcc -Wall client.o SourceClient.o -lm -o client

client.o: client.c HeaderClient.h
	gcc -Wall -c client.c

SourceServer.o: SourceServer.c HeaderServer.h
	gcc -Wall -c SourceServer.c

SourceClient.o: SourceClient.c HeaderClient.h
	gcc -Wall -c SourceClient.c

.PHONY: clean
clean:
	rm -f *.o
	rm server
	rm client
