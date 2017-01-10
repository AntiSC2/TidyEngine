/*
TidyEngine
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
Contact the author at: jakob.sinclair99@gmail.com
*/

#pragma once

#include "renderable.hpp"
#include "texture.hpp"

class Rect2D : public Renderable {
public:
	Rect2D();
	Rect2D(float x, float y, float w, float h);
	Rect2D(glm::vec2 position, glm::vec2 dimensions);
	Rect2D(glm::vec4 rect);
	virtual ~Rect2D();

	virtual void SetRect(float x, float y, float w, float h);
	virtual void SetColor(glm::vec4 color);
	virtual void SetColor(float r, float g, float b, float a);
	virtual void SetTexture(const Texture &tex);
protected:
	glm::vec4 m_Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
};
