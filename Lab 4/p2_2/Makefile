CC = gcc
CFLAGS = -Wall -pthread
TARGET = p2_2

$(TARGET): $(TARGET).o f.o
	$(CC) $(CFLAGS) $(TARGET).o f.o -lm -o $(TARGET)

$(TARGET).o: $(TARGET).c Header.h
	$(CC) $(CFLAGS) -c $(TARGET).c

f.o: f.c Header.h
	$(CC) $(CFLAGS) -c f.c

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)
