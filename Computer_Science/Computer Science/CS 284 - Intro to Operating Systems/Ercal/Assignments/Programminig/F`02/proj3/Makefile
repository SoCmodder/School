
CC=gcc
CFLAGS= -Wall -O2 -g
LFLAGS=

EXE1=prog3
OBJECTS1= prog3.o
EXE2=prog3b
OBJECTS2= prog3b.o

.SUFFIXES: .o .c

all: $(EXE1) $(EXE2)
	true

$(EXE1): $(OBJECTS1)
	$(CC) $(LFLAGS) -o $(EXE1) $(OBJECTS1)

$(EXE2): $(OBJECTS2)
	$(CC) $(LFLAGS) -o $(EXE2) $(OBJECTS2)

.c.o: $*.c
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -rf $(OBJECTS1) $(OBJECTS2) $(EXE1) $(EXE2) core

