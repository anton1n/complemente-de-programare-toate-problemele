CC = gcc
CFLAGS = -Wall -pthread
TARGET = p1_2

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)
