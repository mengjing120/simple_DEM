CC=gcc
CFLAGS=-Wall -O2
LDFLAGS=-lm
#CFLAGS=-Wall -O2 -fopenmp -g -G
#LDFLAGS=-fopenmp
SRC=grains.c initialize.c main.c vtk_export.c walls.c
OBJ=$(SRC:.c=.o)
BIN=simple_DEM
DEPS=header.h global_properties.h

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o:	%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) $(BIN) $(OBJ) output/*

