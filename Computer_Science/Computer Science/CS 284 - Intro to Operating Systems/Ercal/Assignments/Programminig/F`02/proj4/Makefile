
CC=gcc
CFLAGS= -Wall -O2 -g
LFLAGS=

EXE1=prog4
OBJECTS1= prog4.o

.SUFFIXES: .o .c

all: $(EXE1)
	true

$(EXE1): $(OBJECTS1)
	$(CC) $(LFLAGS) -o $(EXE1) $(OBJECTS1)

.c.o: $*.c
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -rf $(OBJECTS1) $(EXE1) core

