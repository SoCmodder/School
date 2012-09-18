
CC = g++ -c
LD = g++

CFLAGS = -Wall -O2
LFLAGS = -s

EXE = proj2
OBJECTS = recursive.o tabular.o greedy.o main.o

all:	$(OBJECTS)
	$(LD) $(LFLAGS) -o $(EXE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm *.o $(EXE); true
