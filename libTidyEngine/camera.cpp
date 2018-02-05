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

#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

Camera::Camera()
{
	;
}

Camera::Camera(uint16_t width, uint16_t height)
{
	Initialise(width, height);
}

Camera::Camera(uint16_t width, uint16_t height, glm::vec3 pos, bool ortho)
{
	Initialise(width, height, pos, ortho);
}
Camera::~Camera()
{
	;
}

void Camera::Initialise(uint16_t width, uint16_t height, glm::vec3 pos, bool ortho)
{
	m_Width = width;
	m_Height = height;
	m_Ortho = ortho;

	if (ortho) {
		m_Position.x = (float)(m_Width / 2) + pos.x;
		m_Position.y = (float)(m_Height / 2) + pos.y;
		m_Position.z = 1.0f;
		InitOrtho();
	} else {
		m_Position = pos;
		InitProj();
	}	
	
	m_Update = false;
}

void Camera::Update()
{
	/* Only update the camera if it has moved, scaled or rotated */
	if (m_Update == true && m_Ortho == true) {
		glm::vec3 translate = glm::vec3(-m_Position.x + m_Width / 2,
		                                -m_Position.y + m_Height / 2,
		                                -m_Position.z);
		m_View = glm::translate(m_View, translate);

		glm::vec3 scale = glm::vec3(m_Scale, m_Scale, 1.0f);
		m_Model = glm::scale(glm::mat4(1.0f), scale);
		m_Update = false;
	} else if (m_Update == true) {
		m_View = glm::lookAt(
			m_Position,
        	m_Position + m_Dir,
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		glm::vec3 scale = glm::vec3(m_Scale, m_Scale, m_Scale);
		m_Model = glm::scale(glm::mat4(1.0f), scale);
		m_Update = false;
	}
}

void Camera::SetScale(float scale)
{
	m_Scale = scale;
	m_Update = true;
}

void Camera::SetPos(glm::vec3 position)
{
	m_Position = position;
	m_Update = true;
}

void Camera::SetDir(glm::vec3 dir)
{
	if (m_Ortho == true)
		return;
	m_Dir = dir;
	m_Update = true;
}

const float &Camera::GetScale() const
{
	return m_Scale;
}

const glm::vec3 &Camera::GetPos() const
{
	return m_Position;
}

const glm::mat4 &Camera::GetProj() const
{
	return m_Projection;
}

const glm::mat4 &Camera::GetView() const
{
	return m_View;
}

const glm::mat4 &Camera::GetModel() const
{
	return m_Model;
}

void Camera::InitOrtho()
{
	m_Projection = glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f,
			0.1f, 100.0f);
	glm::vec3 translate = glm::vec3(-m_Position.x + m_Width / 2,
	                                -m_Position.y + m_Height / 2,
	                                -m_Position.z);
	m_View = glm::translate(m_View, translate);

	glm::vec3 scale = glm::vec3(m_Scale, m_Scale, 1.0f);
	m_Model = glm::scale(glm::mat4(1.0f), scale);
}

void Camera::InitProj()
{
	m_Projection = glm::perspective(glm::radians(70.0f), (float)m_Width / (float)m_Height, 0.1f,
			100.0f);
	m_View = glm::lookAt(
		m_Position,
		m_Position - m_Dir,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	glm::vec3 scale = glm::vec3(m_Scale, m_Scale, m_Scale);
	m_Model = glm::scale(glm::mat4(1.0f), scale);
}
