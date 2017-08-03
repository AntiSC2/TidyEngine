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
#include "camera.hpp"
#include "sprite.hpp"
#include "cache.hpp"
#include "rid.hpp"
#include "luascript.hpp"

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
	Camera *cam = new Camera("MainCamera");
	cam->Initialise(1280, 720, &m_Screen);
	m_EntityManager.SetCamera(cam);
	cam = nullptr;
	m_Font.Initialize(&m_FontLib, "Acme-Regular.ttf", 128);

	Resources.CreateTexture("sprite", "sprite.png");
	Resources.CreateSample("sound", "sound.ogg");
	Resources.GetSample("sound")->Play();

	Sprite *sprite_ref = static_cast<Sprite *>(Resources.CreateResource(
	                     "sprite", new Sprite(Resources.GetTexture("sprite"),
	                     110, 200, {25, 29, 135, 229, 150, 29, 260, 229, 287, 29, 397, 229, 438, 29, 548, 229}))->Data());
	sprite_ref->SetImageSpeed(0.1f);
	Entity *temp = new Entity("hello", "none",
	                          {*Resources.GetResource("sprite")});
	LuaScript script("player.lua");
	int posX = script.Get<int>("player.pos.X");
	int posY = script.Get<int>("player.pos.Y");

	temp->SetPos(glm::vec3((float)posX, (float)posY, 0.0f));
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
	rect.SetRect(0.0f, 680.0f, 1280.0f, 720.0f);
	m_Graphics.Clear();

	m_SpriteRenderer.Begin();
	m_EntityManager.Draw(&m_SpriteRenderer);
	m_SpriteRenderer.Draw(&rect);
	m_SpriteRenderer.DrawText("TidyEngine V0.2", glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), m_Font);
	m_SpriteRenderer.End();
	m_SpriteRenderer.Present(m_EntityManager.GetCamera());

	m_Graphics.Present(m_Screen.GetWindow());
}
