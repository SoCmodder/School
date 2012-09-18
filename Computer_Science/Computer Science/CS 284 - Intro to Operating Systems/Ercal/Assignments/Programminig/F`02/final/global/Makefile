
include ../make/site.mak

OBJECTS = queue.o

.SUFFIXES: .o .c .h

all: $(OBJECTS)

.c.o:	$*.c
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm -rf *.o core

