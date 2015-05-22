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

Core::Core() {
    ;
}

Core::~Core() {
    ;
}

bool Core::init() {
    bool success = true;
    int imgFlags = IMG_INIT_PNG;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    m_Initialized = true;
    return success;
}

void Core::quit() {
    IMG_Quit();
    SDL_Quit();
}
