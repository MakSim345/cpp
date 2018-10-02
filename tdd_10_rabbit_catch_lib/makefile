#makefile

# !include <win32.mak>

GEN = gen.h 
PROGRAM = run.exe
GCC = g++
ALL_OBJ = main.o turtle.o rabbit.o
CFLAGS = -Wall -g

#Link the program:
$(PROGRAM): $(ALL_OBJ)
	$(GCC) -o $(PROGRAM) $(ALL_OBJ)

# All .o files depend on their corresponding .cpp file
%.obj: %.cpp %.h $(GEN)
	$(GCC) $(CFLAGS) -c $<

