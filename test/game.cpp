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
#include "screen.hpp"
#include "rect2d.hpp"
#include "camera.hpp"
#include "sprite.hpp"
#include "cache.hpp"
#include "rid.hpp"
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
	//if (Res.CreateModel("nanosuit", "Model/nanosuit.obj") != nullptr)
	//	m_Model = static_cast<Model*>(Res.GetResource("nanosuit")->Data());

	m_EntityManager.AddEntity<Entity>(std::make_unique<Entity>("Camera"));
	m_EntityManager.GetEntity("Camera").AddComponent<Camera>(std::make_unique<Camera>(1280, 720, &m_Screen));

	m_Font.Initialize(&m_FontLib, "Acme-Regular.ttf", 128);

	Res.CreateTexture("sprite", "sprite.png");
	Res.CreateSample("sound", "sound.ogg");
	Res.GetSample("sound")->Play();

	/*Sprite *sprite_ref = static_cast<Sprite *>(Res.CreateResource(
	                     "sprite", new Sprite(Res.GetTexture("sprite"),
	                     110, 200, {25, 29, 135, 229, 150, 29, 260, 229, 287, 29, 397, 229, 438, 29, 548, 229}))->Data());
	sprite_ref->SetImageSpeed(0.1f);
	Entity *temp = new Entity("hello", "none",
	                          {*Res.GetResource("sprite")});
	LuaScript script("player.lua");
	int posX = script.Get<int>("player.pos.X");
	int posY = script.Get<int>("player.pos.Y");

	temp->SetPos(glm::vec3((float)posX, (float)posY, 0.0f));
	m_EntityManager.AddEntity(temp);*/

	return true;
}

void Game::Update(double delta)
{
	/*
	float speed = 3.0f * (float)delta;
	float xoffset = m_Input.GetMousePos().x - m_LastX;
	float yoffset = m_LastY - m_Input.GetMousePos().y;
	m_LastX = m_Input.GetMousePos().x;
	m_LastY = m_Input.GetMousePos().y;

	float sensitivity = 0.05f;
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
	*/
	if (m_Input.GetKey(GLFW_KEY_ESCAPE))
		m_Screen.CloseWindow();
	else if (m_Input.GetKey(GLFW_KEY_SPACE))
		Res.GetSample("sound")->Play();
	/*if (m_Input.GetKey(GLFW_KEY_W))
		m_Pos += speed * m_Front;
	if (m_Input.GetKey(GLFW_KEY_S))
		m_Pos -= speed * m_Front;
	if (m_Input.GetKey(GLFW_KEY_A))
		m_Pos -= glm::normalize(glm::cross(m_Front, m_Up)) * speed;
	if (m_Input.GetKey(GLFW_KEY_D))
		m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * speed;
	m_EntityManager.GetCamera()->SetPos(m_Pos);
	m_EntityManager.GetCamera()->SetDir(m_Front);*/
}

void Game::DrawGame()
{
	Rect2D rect;
	rect.SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	rect.SetRect(0.0f, 680.0f, 1280.0f, 720.0f);
	m_Graphics.Clear();

	m_SpriteRenderer.Begin();
	m_SpriteRenderer.Draw(&rect);
	m_SpriteRenderer.DrawText("TidyEngine V0.2", glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), m_Font);
	m_SpriteRenderer.End();
	m_SpriteRenderer.Present(m_EntityManager.GetEntity("Camera").GetComponent<Camera>());
	/*m_ModelRenderer.Begin();
	m_Model->Draw(m_Graphics.GetShader("model"));
	m_ModelRenderer.End();
	m_ModelRenderer.Present(m_EntityManager.GetCamera());*/

	m_Graphics.Present(m_Screen.GetWindow());
}
