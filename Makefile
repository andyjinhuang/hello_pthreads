CC = gcc
CFLAGS = -g -Wall -std=gnu99 -D_REENTRANT

PROGS = hello

hello : hello.o
	$(CC) -o $@ hello.o -lpthread

clean :
	rm -f *.o $(PROGS) *~ solution.zip submit.properties

depend :
	$(CC) $(CFLAGS) -M hello.c > depend.mak

depend.mak :
	touch $@

include depend.mak
