
CFLAGS=-I../include -std=c++17 -g
LIBS=-lncurses

AsciiPuzzle: main.cpp Game.cpp Color.cpp World.cpp Camera.cpp Entity.cpp Tile.cpp
	g++ -o $@  $^ $(CFLAGS) $(LIBS)
