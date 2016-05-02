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

#include "sheet.hpp"
#include "texture.hpp"

Sheet::Sheet(uint32_t x, uint32_t y, const Texture *tex)
{
	Initialise(x, y, tex);
}

Sheet::~Sheet()
{
	m_Tex = nullptr;
}

bool Sheet::Initialise(uint32_t x, uint32_t y, const Texture *tex)
{
	if (x == 0 || y == 0 || tex == nullptr)
		return false;
       
	m_TilesX = x;
	m_TilesY = y;
	m_Tex = tex;

	m_TexCoords = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	if (m_Tex->GetWidth() > 0 && m_Tex->GetHeight() > 0) {
		/* the y axis in TidyEngine is pointing down but opengl's y axis
		 * is pointing up which we must reverse else the (0,0) 
		 * coordinate in spritesheets will be in the bottom left corner
		 */
		m_TexCoords.z = 1.0f / (float)x;
		m_TexCoords.y = 1.0f / (float)y;
		m_TexCoords.w = m_TexCoords.y * 2;
	} else {
		m_TilesX = 0;
		m_TilesY = 0;
		m_Tex = nullptr;
		return false;
	}
	return true;
}

GLuint Sheet::GetTex() const
{
	if (m_Tex == nullptr)
		return 0;
	return m_Tex->GetTex();
}

/* the (0,0) coordinate represents the most top left section of the sheet */
const glm::vec4 Sheet::GetTexCoords(uint32_t x, uint32_t y) const
{
	if (x == 0 && y == 0) {
		return m_TexCoords;
	}
	for (; x >= m_TilesX; x -= m_TilesX)
		;
	for (; y >= m_TilesY; y -= m_TilesY)
		;

	glm::vec4 temp(m_TexCoords);
	temp.x += m_TexCoords.z * x;
	temp.y -= m_TexCoords.y * y;
	temp.z += m_TexCoords.z * x;
	temp.w -= m_TexCoords.y * y;
	return temp;
}

const uint32_t &Sheet::GetWidth() const
{
	return m_TilesX;
}

const uint32_t &Sheet::GetHeight() const
{
	return m_TilesY;
}
