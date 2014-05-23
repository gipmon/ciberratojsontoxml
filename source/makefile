CC = g++
CFLAGS = -c -Wall

all: test




test: symboltable.o testsymboltable.o
	$(CC) symboltable.o testsymboltable.o -o test.out
	rm -rf *.o

testsymboltable.o: testsymboltable.cpp
	$(CC) $(CFLAGS) testsymboltable.cpp

symboltable.o:	symboltable.cpp
	$(CC) $(CFLAGS) symboltable.cpp