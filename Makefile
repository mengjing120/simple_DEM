CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=
#CFLAGS=-c -Wall -O2 -fopenmp -g -G
#LDFLAGS=-fopenmp
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=simple_DEM

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) *.o output/*
