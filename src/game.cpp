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
#include <SDL2/SDL_image.h>
#include "cache.h"

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
    if(init()) {
        gameLoop();
    }
    quit();
}

//The init function initializes the engine so that the game can use it
//Returns true if an error did not show up
bool Game::init() {
    bool success = true;
    int imgFlags = IMG_INIT_PNG;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    } else if(m_Screen.createNewWindow(1280, 720, "GameEngine") != true) {
        success = false;
    }
    if(Cache::texCache.createTexture("resources/block.png", m_Screen.getRenderer()) == nullptr) {
        success = false;
    }
    return success;
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
    SDL_Texture* temp = Cache::texCache.getTexture("resources/block.png");
    SDL_RenderClear(m_Screen.getRenderer());
    SDL_RenderCopy(m_Screen.getRenderer(), temp, nullptr, nullptr);
    SDL_RenderPresent(m_Screen.getRenderer());
}

//The quit function makes sure that everything is closed properly
void Game::quit() {
    IMG_Quit();
    SDL_Quit();
}
