#####################################################################
#                                                                   #
# (c) Copyright Yuriy Senishch, 2016                                #
#                                                                   #
#####################################################################

CC = g++
CFLAGS = -Wall -std=c++11 -lpthread

GEN = gen.h 

ALL=  main.cpp

ASM : main.o

	$(CC) -o a.exe main.o -lpthread

main.o : main.cpp $(GEN)
	$(CC) -c main.cpp $(CFLAGS)

clean :
	rm *.o
	rm *.exe
