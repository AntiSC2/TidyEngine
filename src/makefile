#OBJS specifies which files to compile as part of the project
OBJS = main.cpp screen.cpp game.cpp input.cpp cache.cpp texcache.cpp

#CC specifies which compiler to use
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -std=c++14

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME
OBJ_NAME = Game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS)  $(COMPILER_FLAGS) $(LINKER_FLAGS) -o ~/Code/GameEngine/Bin/$(OBJ_NAME)
