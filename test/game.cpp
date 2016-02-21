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


#include "game.hpp"

Game::Game()
{
	;
}

Game::~Game()
{
	;
}

bool Game::Init()
{
	bool success = true;
	if(m_Screen.CreateWindow(1280, 720, "GameEngine") != true) {
		success = false;
        } else {
                glfwSetWindowShouldClose(m_Screen.GetWindow(), GL_FALSE);
        }

	return success;
}

void Game::Update()
{
        glfwPollEvents();
}

void Game::DrawGame()
{
        glfwSwapBuffers(m_Screen.GetWindow());
}
