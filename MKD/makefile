#####################################################################
#                                                                   #
#                              CHE                                  #
#                         ~~~~~~~~~~~~~~                            #
# Makefile for building zpcheck.exe and mkd.exe                     #
#  Common settings.                                                 #
#                                                                   #
#                                                                   #
# (c) Copyright SAVCOR Yuriy Senishch, 2005                         #
#                                                                   #
#####################################################################

CC = gxx
CFLAGS = -Wall
#APPNAME = zpcheck
APPNAME = timediff
GEN = gen.h 

ALL = main.cpp utils.cpp utils.h $(GEN)

$(APPNAME) : main.o utils.o info.o

	$(CC) -o $(APPNAME).exe main.o utils.o info.o

main.o : main.cpp utils.h info.h $(GEN)
	$(CC) -c main.cpp $(CFLAGS)

utils.o : utils.cpp utils.h $(GEN)
	$(CC) -c utils.cpp $(CFLAGS)
	
info.o : info.cpp info.h $(GEN)
	$(CC) -c info.cpp $(CFLAGS)