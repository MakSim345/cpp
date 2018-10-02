#makefile

# !include <win32.mak>

GEN = gen.h 
PROGRAM = plane.exe
GCC = g++
ALL_OBJ = main.o utils.o plane.o error_message.o
CFLAGS = -Wall -g -std=c++11

#Link the program:
$(PROGRAM): $(ALL_OBJ)
	$(GCC) $(ALL_OBJ) -o $(PROGRAM)

# All .o files depend on their corresponding .cpp file
%.obj: %.cpp %.h $(GEN)
	$(GCC) $(CFLAGS) -c $<

clean :
	rm *.o
	rm *.exe
