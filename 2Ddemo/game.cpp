/*
Copyright (C) 2018 Jakob Sinclair

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
}