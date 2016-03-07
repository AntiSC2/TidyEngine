/*
Copyright (C) 2016 Jakob Sinclair

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
#include <GLFW/glfw3.h>
#include "shader.hpp"

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
	return success;
}

void Game::Update()
{
        glfwPollEvents();
}

void Game::DrawGame()
{
	Rect2D m_Rect;
	m_Rect.SetRect(0.0f, 0.0f, 1.0f, 1.0f);
	m_Rect.SetColor(0.2f, 0.3f, 0.4f, 1.0f);
        m_2DRender.Clear();
        m_DrawSprite.Begin();
        m_DrawSprite.Draw(m_Rect);
        m_DrawSprite.End();
        m_DrawSprite.Present();
        m_2DRender.Present(m_Screen.GetWindow());
}
