
HOMEDIR = /afs/umr.edu/users/jwing

MAKE = gmake
CC = gcc
CFLAGS = -g -Wall -I$(HOMEDIR)/include
LFLAGS = -L/usr/lib -L$(HOMEDIR)/lib -L.. -lXm -lXt -lX11 -lXpm -lpthread -lm

