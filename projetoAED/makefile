# This is a general solution for a makefile

CC=gcc
CFLAGS=-c -ansi -Wall -O3
LDFLAGS=
SOURCES=ISTravel.c Defs.c LinkedList.c Utilities.c Graph.c Bridge.c Heap.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=istravel

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o *.~ $(EXECUTABLE) *.gch

backup:
	rm -rf backup.zip
	zip -r -9 backup.zip *.c *.h makefile
