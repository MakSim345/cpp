#makefile

# !include <win32.mak>

GEN = gen.h 
PROGRAM = phone_book.exe
GCC = g++
ALL_OBJ = mainc.o phone_book.o cTimer.o
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
