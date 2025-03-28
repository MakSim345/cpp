#####################################################################
#                         ~~~~~~~~~~~~~~                            #
# (c) Copyright Yuriy Senishch, 2016                                #
#                                                                   #
#####################################################################

CC = g++
CFLAGS = -Wall -std=c++11 -pthread

GEN = gen.h 

ALL=  main.cpp

ASM : main.o

	$(CC) -o a.out main.o -pthread

main.o : main.cpp $(GEN)
	$(CC) -c main.cpp $(CFLAGS)

clean :
	rm *.o
	rm *.out
