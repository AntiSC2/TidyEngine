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

//Error 001: SDL window could not be created, probably because of SDL not being initialized correctly
//Error 002: SDL_image could not load image, probably because of SDL not being initialized correctly
//Error 003: SDL could not create texture from surface
//Error 004: SDL could not create renderer

#include "game.h"
#include "config.h"

int main(int argc, char** argv) {
    printf("TidyEngine Version: %d.%d\n", TidyEngine_VERSION_MAJOR, TidyEngine_VERSION_MINOR);
    Game g;
    g.run();
    return 0;
}
