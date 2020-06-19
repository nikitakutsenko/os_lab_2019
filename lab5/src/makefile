CC=gcc
CFLAGS=-I. -pthread

all : clean deadlock fact mutex

deadlock : deadlock.o
	$(CC) -o deadlock deadlock.o $(CFLAGS)

deadlock.o :
	$(CC) -c deadlock.c $(CFLAGS)

fact : factorial.o
	$(CC) -o fact factorial.o $(CFLAGS)

factorial.o :
	$(CC) -c factorial.c $(CFLAGS)

mutex : mutex.o
	$(CC) -o mutex mutex.o $(CFLAGS) $(mx)

mutex.o :
	$(CC) -c mutex.c $(CFLAGS)

clean :
	rm -f *.o mutex fact deadlock
