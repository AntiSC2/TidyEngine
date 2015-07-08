#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Graphics/screen.cpp game.cpp Core/input.cpp RM/cache.cpp RM/texcache.cpp Core/core.cpp Components/component.cpp Components/controller.cpp Components/sprite.cpp Entities/actor.cpp Graphics/spritesheet.cpp RM/sheetcache.cpp

#CC specifies which compiler to use
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -std=c++14

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of the final executable
OBJ_NAME = Game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS)  $(COMPILER_FLAGS) $(LINKER_FLAGS) -o ~/Code/GameEngine/Bin/$(OBJ_NAME)
