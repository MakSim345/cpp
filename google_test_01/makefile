#makefile


PROGRAM = pers.exe
ALL_OBJ = main.o person.o

CFLAGS = -Wall -g

GEN = gen.h 
GCC = gcc
GPP = g++

all:
	$(GCC) -c ./*.cpp
	$(GPP) ./test.cpp person.o /usr/lib/libgtest.a -o runTest.exe -fPIC -O2 -g -Wall -lpthread

clean :
	rm *.o
	rm *.out
