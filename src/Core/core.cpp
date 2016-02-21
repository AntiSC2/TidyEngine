/*
Copyright (C) 2015 Jakob Sinclair

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "core.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

Core::Core() {
	;
}

Core::~Core() {
	;
}

void Core::run() {
	if(initSubSystems() && init()) {
		gameLoop();
	}
	quit();
}

bool Core::initSubSystems() {
    	bool success = true;
    	int imgFlags = IMG_INIT_PNG;
	
    	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	} else if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	} else if(TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	
	return success;
}

//The init function handles the initialization of the game
bool Core::init() {
	bool success = true;
	m_Initialized = true;
	return success;
}

void Core::gameLoop() {
	while(m_Input.getCloseWindow() != true) {
		update();
		drawGame();
	}    
}

void Core::update() {
	m_Input.update();
}

void Core::drawGame() {
	;
}

void Core::quit() {
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

























