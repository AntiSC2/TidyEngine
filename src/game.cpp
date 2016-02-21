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

Game::Game() {
	;
}

Game::~Game() {
	;
}

bool Game::init() {
	bool success = true;

    	if(m_Screen.createNewWindow(1280, 720, "GameEngine") != true) {
		success = false;
	}

	return success;
}

void Game::update() {
        ;
}

void Game::drawGame() {
        ;
}