
CC = cc
CFLAGS = -g -D_REENTRANT

all:
	$(CC) $(CFLAGS) -o client client.c -lsocket -lnsl -lthread
	$(CC) $(CLFAGS) -o server server.c -lsocket -lnsl -lthread

clean:
	rm -f client server *.o core


