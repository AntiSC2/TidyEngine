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
	cam->Initialise(1280, 720);
	m_ObjectManager.SetCamera(cam);
	m_ObjectManager.AddObject(cam);
	cam = nullptr;

	Resources.CreateTexture("sprite", "sprite.png");
	Resources.CreateSample("sound", "sound.ogg");
	Resources.GetSample("sound")->Play();

	RID *temp = nullptr;
	temp = Resources.CreateResource("sheet", new Sheet(2, 2,
	                                Resources.GetTexture("sprite")));
	Resources.CreateResource("sprite", new Sprite(temp, 32, 32,
	                         {0, 0, 1, 0,0, 1, 1, 1}));
	temp = nullptr;
	Sprite *temp3 = boost::any_cast<Sprite *>(Resources.GetResource("sprite")->Data());
	if (temp3 == nullptr) {
		printf("Fuck");
	}
	
	Object *temp2 = new Object("hello", "none",
	                          {*Resources.GetResource("sprite")});
	m_ObjectManager.AddObject(temp2);
	return true;
}

void Game::Update()
{
	m_Input.Update();
	m_ObjectManager.Update();
	if (m_Input.GetKey(GLFW_KEY_ESCAPE))
		m_Screen.CloseWindow();
	else if (m_Input.GetKey(GLFW_KEY_SPACE))
		Resources.GetSample("sound")->Play();
}

void Game::DrawGame()
{
	m_Render.Clear();

	m_SpriteRenderer.Begin();
	m_ObjectManager.Draw(&m_SpriteRenderer);
	m_SpriteRenderer.End();
	m_SpriteRenderer.Present(m_ObjectManager.GetCamera());

	m_Render.Present(m_Screen.GetWindow());
}
