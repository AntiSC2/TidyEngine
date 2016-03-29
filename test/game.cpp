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
#include "screen.hpp"
#include "rect2d.hpp"
#include "camera2d.hpp"
#include "sprite.hpp"
#include "sheet.hpp"
#include "cache.hpp"

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
        Camera2D *temp = new Camera2D();
        temp->Initialise(1280, 720);
        m_ObjectManager.SetCamera(temp);
        m_ObjectManager.AddObject(temp);
        temp = nullptr;
        Resources.CreateTexture("sprite", "sprite.png");

	return true;
}

void Game::Update()
{
        m_Input.Update();
        m_ObjectManager.Update();
        if (m_Input.GetKey(GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(m_Screen.GetWindow(), GL_TRUE);
}

void Game::DrawGame()
{
        Sheet sheet(2, 2, &Resources.GetTexture("sprite"));
        Sprite temp(&sheet, 64, 64);
        temp.SetPos(glm::vec3(500.0f, 200.0f, 0.0f));
        m_Render.Clear();

        m_DrawSprite.Begin();
        m_DrawSprite.Draw(&temp);
        m_ObjectManager.Draw(&m_DrawSprite);
        m_DrawSprite.End();
        m_DrawSprite.Present(m_ObjectManager.GetCamera());

        m_Render.Present(m_Screen.GetWindow());
}
