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
#include "cache.hpp"
#include "rid.hpp"

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
	Camera2D *cam = new Camera2D("MainCamera");
	cam->Initialise(1280, 720, &m_Screen);
	m_EntityManager.SetCamera(cam);
	m_EntityManager.AddEntity(cam);
	cam = nullptr;
	m_Font.Initialize(&m_FontLib, "modern_squared2.ttf", 128);

	Resources.CreateTexture("sprite", "sprite.png");
	Resources.CreateSample("sound", "sound.ogg");
	Resources.GetSample("sound")->Play();

	Resources.CreateResource("sprite", new Sprite(Resources.GetTexture("sprite"), 32, 32,
	                         {0, 0, 32, 32, 0, 32, 32, 64}));
	static_cast<Sprite *>(Resources.GetResource("sprite")->Data())->SetImageSpeed(0.1f);
	Entity *temp = new Entity("hello", "none",
	                          {*Resources.GetResource("sprite")});
	m_EntityManager.AddEntity(temp);
	
	return true;
}

void Game::Update()
{
	m_Input.Update();
	m_EntityManager.Update();
	if (m_Input.GetKey(GLFW_KEY_ESCAPE))
		m_Screen.CloseWindow();
	else if (m_Input.GetKey(GLFW_KEY_SPACE))
		Resources.GetSample("sound")->Play();
}

void Game::DrawGame()
{
	Rect2D rect;
	rect.SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	rect.SetRect(640.0f, -180.0f, 640.0f, 360.0f);
	m_Render.Clear();

	m_SpriteRenderer.Begin();
	m_EntityManager.Draw(&m_SpriteRenderer);
	m_SpriteRenderer.Draw(&rect);
	m_SpriteRenderer.DrawText("TidyEngine V0.2", glm::vec2(0.0f, 64.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), m_Font);
	m_SpriteRenderer.End();
	m_SpriteRenderer.Present(m_EntityManager.GetCamera());

	m_Render.Present(m_Screen.GetWindow());
}
