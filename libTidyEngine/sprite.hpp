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

class Texture;
class RID;

#include <cstdint>
#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "renderable.hpp"
#include "component.hpp"
#include "vertex.hpp"

class Sprite : public Renderable, public Component {
public:
	Sprite(const Texture *tex, uint32_t w = 0, uint32_t h = 0,
	       const std::vector<uint32_t> &frames = {0, 0});
	virtual ~Sprite();

	virtual void Update();
	virtual void Render();
	virtual bool Initialise(const Texture *tex, uint32_t w = 0, uint32_t h = 0, 
	                        const std::vector<uint32_t> &frames = {0, 0, 0, 0});
	virtual const glm::vec3 &GetPos() const;
	virtual const uint32_t &GetWidth() const;
	virtual const uint32_t &GetHeight() const;
	virtual void SetPos(const glm::vec3 &pos);
	virtual void SetWidth(uint32_t w);
	virtual void SetHeight(uint32_t h);
	virtual void SetImageIndex(uint32_t image_index);
	virtual void SetImageSpeed(float speed);
protected:
	float m_ImageSpeed = 0.0f;
	float m_ImageBuffer = 0.0f;
	uint32_t m_ImageIndex = 0;
	uint32_t m_Width = 0;
	uint32_t m_Height = 0;
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	std::vector<glm::vec4> m_Frames = {};
	const Texture *m_Texture = nullptr;
	bool m_Update = false;
};
