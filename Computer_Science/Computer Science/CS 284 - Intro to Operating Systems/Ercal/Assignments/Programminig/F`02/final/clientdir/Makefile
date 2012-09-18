
include ../make/site.mak

OBJECTS = display.o client.o event.o main.o network.o

.SUFFIXES: .o .c .h

all:	client

client:	$(OBJECTS)
	$(CC) -o client $(OBJECTS) $(LFLAGS)

.c.o:	$*.c
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm -rf *.o core client

