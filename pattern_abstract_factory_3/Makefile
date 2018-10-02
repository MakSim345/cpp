CXX=g++
NAME=AbstractFactory
EXECUTABLE=run_AbstractMethod
CFLAGS=-Wall $(INCLUDE_DIRS) -O
INCLUDE_DIRS=-Iinclude -I$(BOMBED_DIR)/include
BASE_SOURCES=main.o Door.o Maze.o MazeGame.o Room.o Wall.o
BOMBED_DIR=Bombed
BOMBED=BombedMazeGame.o BombedWall.o RoomWithABomb.o
PLUGINS=$(BOMBED)
SOURCES=$(BASE_SOURCES) $(PLUGINS)

all: $(NAME)

$(NAME): $(SOURCES)
	$(CXX) $(SOURCES) -o $(EXECUTABLE)

main.o: main.cpp include/main.h
	$(CXX) -c $(CFLAGS) main.cpp

Door.o: Door.cpp include/Door.h include/Room.h include/MapSite.h
	$(CXX) -c $(CFLAGS) Door.cpp

Maze.o: Maze.cpp include/Maze.h include/Room.h
	$(CXX) -c $(CFLAGS) Maze.cpp

MazeGame.o: MazeGame.cpp include/MazeGame.h include/Room.h include/Door.h include/Wall.h
	$(CXX) -c $(CFLAGS) MazeGame.cpp

Room.o: Room.cpp include/Room.h include/main.h include/MapSite.h
	$(CXX) -c $(CFLAGS) Room.cpp

Wall.o: Wall.cpp include/Wall.h include/main.h include/MapSite.h
	$(CXX) -c $(CFLAGS) Wall.cpp

BombedMazeGame.o: $(BOMBED_DIR)/BombedMazeGame.cpp $(BOMBED_DIR)/include/BombedMazeGame.h $(BOMBED_DIR)/include/BombedWall.h $(BOMBED_DIR)/include/RoomWithABomb.h
	$(CXX) -c $(CFLAGS) $(BOMBED_DIR)/BombedMazeGame.cpp

BombedWall.o: $(BOMBED_DIR)/BombedWall.cpp $(BOMBED_DIR)/include/BombedWall.h
	$(CXX) -c $(CFLAGS) $(BOMBED_DIR)/BombedWall.cpp

RoomWithABomb.o: $(BOMBED_DIR)/RoomWithABomb.cpp $(BOMBED_DIR)/include/RoomWithABomb.h
	$(CXX) -c $(CFLAGS) $(BOMBED_DIR)/RoomWithABomb.cpp

clean:
	rm -rf *.o $(EXECUTABLE)
