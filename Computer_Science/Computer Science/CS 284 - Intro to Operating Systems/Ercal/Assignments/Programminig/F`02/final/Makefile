
include make/site.mak

all: remove client server

remove:
	rm -f client server

client:
	cd clientdir ;		\
	$(MAKE) client ;	\
	mv client ..

server:
	cd serverdir ;		\
	$(MAKE) server ;	\
	mv server ..

clean:
	cd clientdir ;		\
	$(MAKE) clean ;	\
	cd ../serverdir ;	\
	$(MAKE) clean ;	\
	cd .. ;				\
	rm -rf *.o core server client

kloc:
	wc `find . \( -name "*.c" -o -name "*.h" -o -name "*.xpm" \)`

