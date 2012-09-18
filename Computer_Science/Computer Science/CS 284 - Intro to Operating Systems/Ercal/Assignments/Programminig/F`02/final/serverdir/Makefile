
include ../make/site.mak

OBJECTS = server.o parse.o file.o object.o astar.o

.SUFFIXES: .o .c .h

all:	server

server:	$(OBJECTS)
	$(CC) -o server $(OBJECTS) ../global/queue.o $(LFLAGS)

.c.o:	$*.c
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm -rf *.o core server

