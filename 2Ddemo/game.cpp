/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "game.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "entity.hpp"
#include "shader.hpp"
#include "input.hpp"
#include "graphics.hpp"
#include "rect2d.hpp"
#include "camera.hpp"
#include "sprite.hpp"
#include "cache.hpp"
#include "luascript.hpp"
#include "iomanager.hpp"

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
	m_EM.AddEntity<Entity>(std::make_unique<Entity>("Camera"));
	m_EM.GetEntity("Camera").AddComponent<Camera>(std::make_unique<Camera>(1280, 720));	

	Res.LoadSample("sound.ogg")->Play();
	m_EM.GetSystem<Graphics>().RegisterComponent(std::type_index(typeid(Sprite)));

	m_EM.AddEntity<Entity>(std::make_unique<Entity>("Player"));
	auto &sprite = m_EM.GetEntity("Player").AddComponent<Sprite>(std::make_unique<Sprite>(Res.LoadTex("sprite.png"),
	                                        110, 200,
	                                        std::vector<uint32_t>({25, 29, 135, 229, 150, 29, 260, 229, 287, 29, 397, 229, 438, 29, 548, 229})));	

	LuaScript script("player.lua");
	int posX = script.Get<int>("player.pos.X");
	int posY = script.Get<int>("player.pos.Y");

	sprite.SetImageSpeed(0.1f);
	sprite.SetPos(glm::vec3((float)posX, (float)posY, 0.0f));

	return true;
}

void Game::Update(double delta)
{
	if (m_EM.GetSystem<Input>().GetKey(GLFW_KEY_ESCAPE))
		m_Quit = true;
	else if (m_EM.GetSystem<Input>().GetKey(GLFW_KEY_SPACE))
		Res.LoadSample("sound.ogg")->Play();
	m_EM.GetSystem<Graphics>().Execute(true);
}