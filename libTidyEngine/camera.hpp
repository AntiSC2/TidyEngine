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

#pragma once

#include <glm/mat4x4.hpp>
#include <cstdint>
#include "component.hpp"

class Camera : public Component {
public:
	Camera();
	Camera(uint16_t width, uint16_t height);
	Camera(uint16_t width, uint16_t height, glm::vec3 pos, bool ortho);
	virtual ~Camera();

	void Initialise(uint16_t width = 0, uint16_t height = 0,
	                glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), bool ortho = true);	
	virtual void Update();
	void SetScale(float scale = 1.0f);
	void SetPos(glm::vec3 position);
	void SetDir(glm::vec3 dir);
	const float &GetScale() const;
	const glm::vec3 &GetPos() const;
	const glm::mat4 &GetProj() const;
	const glm::mat4 &GetView() const;
	const glm::mat4 &GetModel() const;
private:
	void InitOrtho();
	void InitProj();

	float m_Scale = 1.0f;
	bool m_Ortho = true;
	bool m_Update = false;
	uint16_t m_Width = 0;
	uint16_t m_Height = 0;
	glm::mat4 m_Model = glm::mat4(1.0f);
	glm::mat4 m_View = glm::mat4(1.0f);
	glm::mat4 m_Projection = glm::mat4(1.0f);
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Dir = glm::vec3(0.0f, 0.0f, -1.0f);
};
