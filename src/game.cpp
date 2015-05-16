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

//The gameLoop function handles the main loop  TEMP:ONLY DISPLAYS WINDOW IN 5 SECONDS
void Game::gameLoop() {
    SDL_Delay(5000);
}

//The update function handles the game updates
void Game::update() {
    ;
}

//The draw function handles the rendering part of the game
void Game::drawGame() {
    ;
}

//The quit function makes sure that everything is closed properly
void Game::quit() {
    SDL_Quit();
}
