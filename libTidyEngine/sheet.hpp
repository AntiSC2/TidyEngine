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

class Texture;

#include <glad/glad.h>
#include <cstdint>
#include <glm/vec4.hpp>
#include "resource.hpp"

class Sheet: public Resource {
public:
	/* x and y stand for the number of tiles to divide the texture in,
	 * not the overall size of the texture
	 */
	Sheet(uint32_t x = 0, uint32_t y = 0, const Texture *tex = nullptr);
	virtual ~Sheet();
	
	virtual std::string Type();

	bool Initialise(uint32_t x, uint32_t y, const Texture *tex);
	const glm::vec4 GetTexCoords(uint32_t x, uint32_t y) const;
	GLuint GetTex() const; 
	const uint32_t &GetWidth() const;
	const uint32_t &GetHeight() const;
protected:
	uint32_t m_TilesX = 0;
	uint32_t m_TilesY = 0;

	glm::vec4 m_TexCoords = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	const Texture *m_Tex = nullptr;
};
