
CC= c++
CFLAGS= -Wall -O2
LFLAGS= -s
RM= rm

FILES= genmat genadj kruskal

all:	$(FILES)

.cpp:
	$(CC) $(CFLAGS) -o $* $<

clean:
	$(RM) $(FILES)
	true;
