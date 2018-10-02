COMPILER = g++
FLAGS = -ggdb
TARGET = ./main
LINK = ./main.o

all : $(TARGET)

clean : 
	rm -f $(TARGET) $(LINK)

$(TARGET) : $(LINK)
	$(COMPILER) $(LINK) $(FLAGS) -o $(TARGET)

%.o : %.cpp
	$(COMPILER) $(FLAGS) -c $<
