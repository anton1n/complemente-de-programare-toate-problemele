TARGET = prob3
MAIN = prob3.c
SOURCE = prelucrare.c
OBJECT1= prob3.o
OBJECT2= prelucrare.o
HEADER = prelucrare.h
CC = gcc 
CFLAGS = -Wall -g 
LIBS = -lm 

$(TARGET): $(OBJECT1) $(OBJECT2) 
	$(CC) $(CFLAGS) $(OBJECT1) $(OBJECT2) $(LIBS) -o $(TARGET) 
		    
$(OBJECT1): $(MAIN) $(HEADER) 
	$(CC) -c $(CFLAGS) $(MAIN) -o $(OBJECT1) 

$(OBJECT2): $(SOURCE) $(HEADER) 
	$(CC) -c $(CFLAGS) $(SOURCE) -o $(OBJECT2) 

.PHONY: clean 
clean: 
	rm -f *.o  
	rm $(TARGET) 
