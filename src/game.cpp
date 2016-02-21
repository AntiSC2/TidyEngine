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
#include "RM/cache.h"
#include "Graphics/spritesheet.h"
#include "Components/sprite.h"
#include "Components/controller.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//The constructor and destructor is nothing special in this case
Game::Game() {
	;
}

Game::~Game() {
	;
}

//The init function initializes the game, true if an error did not show up
bool Game::init() {
	bool success = true;

    	if(m_Screen.createNewWindow(1280, 720, "GameEngine") != true) {
		success = false;
	}

	Cache::loadTexturesFromBlock("resources/game.txt", 1,
		m_Screen.getRenderer());
	Cache::sheetCache.createSheet("resources/block.png");
	Cache::fontCache.createFont("resources/DroidSans.ttf", 20);
	Controller *temp3 = new Controller;
	temp3->initialize("controller", &m_Player);
	temp3->setInputReference(m_Input);
	m_Player.addComponent(temp3);
	temp3 = nullptr;
	SDL_Rect temp2;
	temp2.x = 0; temp2.y = 0; temp2.w = 64; temp2.h = 64;
	Sprite* temp = new Sprite;
	temp->initialize("sprite", &m_Player);
	temp->loadSpriteFromSheet(
		Cache::sheetCache.getSheet("resources/block.png"), temp2, 3);
	m_Player.addComponent(temp);
	temp = nullptr;
	return success;
}

//The update function handles the game updates
void Game::update() {
	m_Input.update();
	m_Player.update();
}

//The draw function handles the rendering part of the game
void Game::drawGame() {
	SDL_Color color = {0, 255, 0, 255};
	SDL_RenderClear(m_Screen.getRenderer());
	draw.begin();
	m_Player.draw(draw);
	draw.drawText("Hello World", "resources/DroidSans.ttf",
		glm::vec2(64.0f, 64.0f), color, m_Screen.getRenderer());
	draw.end();
	draw.render(m_Screen.getRenderer());
	SDL_RenderPresent(m_Screen.getRenderer());
}
