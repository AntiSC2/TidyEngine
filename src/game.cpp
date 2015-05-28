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
#include "cache.h"
#include "spritesheet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//The constructor and destructor is nothing special in this case
Game::Game() {
    ;
}

Game::~Game() {
    ;
}

//The run function is used to run the game
void Game::run() { //Only run the main loop if it initialized properly
    if(init()) {
        gameLoop();
    }
}

//The init function initializes the game, true if an error did not show up
bool Game::init() {
    bool success = true;

    if(m_Screen.createNewWindow(1280, 720, "GameEngine") != true) {
        success = false;
    } else if(Cache::texCache.createTexture("resources/block.png", m_Screen.getRenderer()) == nullptr) {
        success = false;
    }
    return success;
}

//The gameLoop function handles the main loop
void Game::gameLoop() {
    while(m_Input.getCloseWindow() != true) { //As long as the user has not tried to exit
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
    SpriteSheet* temp = new SpriteSheet;
    temp->loadSpriteSheet("resources/block.png");
    SDL_RenderClear(m_Screen.getRenderer());
    temp->renderSprite(64, 64, nullptr, m_Screen.getRenderer());
    SDL_RenderPresent(m_Screen.getRenderer());
}
