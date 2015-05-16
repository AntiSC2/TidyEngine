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


#include "game.h"
#include <SDL2/SDL.h>

//The constructor and destructor is nothing special in this case
Game::Game() {
    ;
}

Game::~Game() {
    ;
}
//The run function is used to run the game, it initializes the engine system, then runs the main loop
//and then exits everything
void Game::run() {
    init();
    gameLoop();
    quit();
}

//The init function initializes the engine so that the game can use it
void Game::init() {
    SDL_Init(SDL_INIT_VIDEO);
    m_Screen.createNewWindow(1280, 720, "GameEngine");
}

//The gameLoop function handles the main loop
void Game::gameLoop() {
    while(m_Input.getCloseWindow() != true) {
        update();
        drawGame();
    }
}

//The update function handles the game updates
void Game::update() {
    m_Input.update();
}

//The draw function handles the rendering part of the game
void Game::drawGame() {
    SDL_UpdateWindowSurface(m_Screen.getWindow());
}

//The quit function makes sure that everything is closed properly
void Game::quit() {
    SDL_Quit();
}
