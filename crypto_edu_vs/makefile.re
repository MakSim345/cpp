#####################################################################
#                                                                   #
#                              CHE                                  #
#                         ~~~~~~~~~~~~~~                            #
# Makefile for building release version of CHE exe.                 #
#                                                                   #
# NOTE 1: there are program compile flags, which must be set        # 
# according to CHE code; see source files.                          #
# NOTE 2: When you do modifications in source code so that included #
# files change, you must do similar changes to this files by hand.  # 
# This file must be updated every time you change include's.        #
#                                                                   #
# (c) Savcor One Oy, 10.12.2001                                     #
#                                                                   #
#####################################################################

# these are common to all
CC = gxx
CFLAGS = -Wall
LDLIBS = -lm -ldzcom -lalleg

# program compile flags; If you want to i.e. optimize compilation, 
# these must be the same as in define-file: gen.h. If you don't
# care ... just set all: ON (-> safe compilation). 
