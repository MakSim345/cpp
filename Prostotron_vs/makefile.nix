# Generic MinGW makefile

# make / make all | will compile your program.
# make clean      | deletes all compiled object and executable files.
# make depend     | rebuilds the dependancy list
# make run        | compiles (if needed) and runs your program

# Compiler command
CC = g++

# Linker command
LD = g++

# Flags to pass to the compiler - add "-g" to include debug information
CFLAGS = -Wall -g

# Flags to pass to the linker
LDFLAGS = -mwindows

# Command used to delete files
RM = del

# List your object files here
OBJS = main.o processor.o memory.o mem_cell.o utils.o

# List your source files here
SRCS = main.cpp memory.cpp processor.cpp utils.cpp mem_cell.cpp\
      gen.h memory.h processor.h utils.h mem_cell.h


# Define your compile target here.
PROG = app2.exe

# Compile everything.
all: $(PROG)

# Link the program
$(PROG): $(OBJS)
	$(LD) $(OBJS) -o $(PROG)
#	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

# All .o files depend on their corresponding .cpp file
%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

#main.o: main.cpp utils.h
#	$(CC) $(CFLAGS) -c main.cpp

#utils.o: utils.cpp utils.h
#	$(CC) $(CFLAGS) -c utils.cpp

clean:
	$(RM) $(PROG)
	$(RM) *.o
	$(RM) depend

depend:
	$(CC) $(CFLAGS) -MM $(SRCS) > depend

run: all
	$(PROG)

#include depend

