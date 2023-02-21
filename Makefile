CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: Player Game main test


Player: 
	$(CXX) $(CXXFLAGS) Player.cpp -c -o Player.o

Game: 
	$(CXX) $(CXXFLAGS) Game.cpp -c -o Game.o

main: Player.o Game.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Player.o Game.o -o main

test: Player.o Game.o test.cpp
	$(CXX) $(CXXFLAGS) test.cpp Player.o Game.o -o test

clean: 
	rm test Player.o Game.o main