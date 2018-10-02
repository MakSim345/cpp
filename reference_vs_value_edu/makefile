#####################################################################
#                                                                   #
#                              CHE                                  #
#                         ~~~~~~~~~~~~~~                            #
# Makefile for building kapTa.exe. Common settings.                 #
#                                                                   #
# NOTE 1: there are program compile flags, which must be set        # 
# according to code; see source files.                              #
# NOTE 2: When you do modifications in source code so that included #
# files change, you must do similar changes to this files by hand.  # 
# This file must be updated every time you change include's.        #
#                                                                   #
#                                                                   #
#####################################################################

CC = g++
CFLAGS = -Wall
APPMNAME = kapTa.exe
GEN = gen.h 

ALL_OBJ = mainc.o utils.o deck.o

$(APPMNAME) : $(ALL_OBJ)
	$(CC) -o $(APPMNAME) $(ALL_OBJ)

mainc.o : mainc.cpp $(GEN) utils.h
	$(CC) -c mainc.cpp $(CFLAGS)

utils.o : utils.cpp $(GEN) utils.h
	$(CC) -c utils.cpp $(CFLAGS)

deck.o : deck.cpp $(GEN) deck.h
	$(CC) -c deck.cpp $(CFLAGS)

clean :
	rm *.o
	rm $(APPMNAME)
