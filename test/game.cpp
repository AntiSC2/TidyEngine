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
	if(m_Screen.CreateWindow(1280, 720, "GameEngine", 3, 3) != true) {
		success = false;
                printf("Error: glfw could not create window!\n");
        } else {
                if (m_Screen.InitGL() == false) {
                        printf("Error: could not initialize OpenGL!\n");
                }
        }
        m_2DRender.GetBatch().Initialise();
	m_2DRender.LoadShaders("default", "shader.vert", "shader.frag",
				 {"position", "color", "uv"});
	m_2DRender.GetShader("default")->Bind();
	m_Rect.SetRect(0.0f, 0.0f, 1.0f, 1.0f);

	return success;
}

void Game::Update()
{
        glfwPollEvents();
}

void Game::DrawGame()
{
        m_2DRender.Clear();
        m_2DRender.GetBatch().Begin();
        m_2DRender.GetBatch().Draw(m_Rect);
        m_2DRender.GetBatch().End();
        m_2DRender.GetBatch().Present();
        m_2DRender.Present(m_Screen.GetWindow());
}
