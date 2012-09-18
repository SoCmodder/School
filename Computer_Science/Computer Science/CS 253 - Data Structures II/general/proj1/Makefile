
CC = cc -c
LD = cc

CFLAGS = -O2 -Wall
LFLAGS = -pg

EXE = sort

OBJECTS = bubble.o heap.o insert.o merge.o mli.o proxmap.o	\
	quick.o radix.o select.o shell.o sort.o

all: $(OBJECTS) check.o gen.o
	$(LD) $(LFLAGS) -o $(EXE) $(OBJECTS)
	$(LD) $(LFLAGS) -o check check.o
	$(LD) $(LFLAGS) -o gen gen.o

clean:
	rm *.o; true
	rm $(EXE); true
	rm check; true
	rm gen; true

.c.o:
	$(CC) $(CFLAGS) $<
