source = main.cpp rubiks.cpp rubiks.h stage3.cpp
all: rubiks

rubiks: $(source)
	g++ $(source) -o rubiks -g -Wall
