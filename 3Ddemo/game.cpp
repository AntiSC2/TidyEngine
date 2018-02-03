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
	m_EM.GetEntity("Camera").AddComponent<Camera>(std::make_unique<Camera>(1280, 720, m_Pos, false));

	Res.LoadSample("sound.ogg")->Play();
	m_EM.GetSystem<Graphics>().RegisterComponent(std::type_index(typeid(Sprite)));

	m_EM.AddEntity<Entity>(std::make_unique<Entity>("Player"));

	return true;
}

void Game::Update(double delta)
{
	auto &input = m_EM.GetSystem<Input>();

	float speed = 10.0f * (float)delta;
	float xoffset = input.GetMousePos().x - m_LastX;
	float yoffset = m_LastY - input.GetMousePos().y;
	m_LastX = input.GetMousePos().x;
	m_LastY = input.GetMousePos().y;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	m_Yaw += xoffset;
	m_Pitch +=  yoffset;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	else if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);

	if (input.GetKey(GLFW_KEY_ESCAPE))
		m_Quit = true;
	else if (input.GetKey(GLFW_KEY_SPACE))
		Res.LoadSample("sound.ogg")->Play();
	if (input.GetKey(GLFW_KEY_W))
		m_Pos += speed * m_Front;
	if (input.GetKey(GLFW_KEY_S))
		m_Pos -= speed * m_Front;
	if (input.GetKey(GLFW_KEY_A))
		m_Pos -= glm::normalize(glm::cross(m_Front, m_Up)) * speed;
	if (input.GetKey(GLFW_KEY_D))
		m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * speed;
	if (input.GetKey(GLFW_KEY_F)) {
		if (m_Locked == false) {
			glfwSetInputMode(m_EM.GetSystem<Graphics>().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_Locked = true;
		} else {
			glfwSetInputMode(m_EM.GetSystem<Graphics>().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_Locked = false;
		}
	}
	auto &camera = m_EM.GetEntity("Camera").GetComponent<Camera>();
	camera.SetPos(m_Pos);
	camera.SetDir(m_Front);
	camera.Update();
}