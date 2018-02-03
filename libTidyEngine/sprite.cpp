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

#include "sprite.hpp"
#include <cmath>
#include <glm/vec2.hpp>
#include "renderable.hpp"
#include "vertex.hpp"
#include "texture.hpp"

Sprite::Sprite(const Texture *tex, uint32_t w, uint32_t h,
		const std::vector<uint32_t> &frames)
{
	Initialise(tex, w, h, frames);
}

Sprite::~Sprite()
{
	;
}

void Sprite::Update()
{
	if (m_Frames.size() < 2)
		return;

	m_ImageBuffer += m_ImageSpeed;
	uint32_t change = m_ImageIndex;
	m_ImageIndex = (uint32_t)std::round(m_ImageBuffer);

	if (m_ImageIndex != change)
		m_Update = true;

	while (m_ImageIndex > (uint32_t)m_Frames.size()) {
		m_ImageBuffer -= (float)m_Frames.size();
		m_ImageIndex -= (uint32_t)m_Frames.size();
	}
}

void Sprite::Render()
{
	if (!m_Update)
		return;

	if (m_Vertices.size() != 6) {
		m_Vertices.clear();
		Vertex temp;
		for (uint8_t i = 0; i < 6; i++)
			AddVertex(temp);
	}

	glm::vec4 tex_coords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	if (m_Frames.size() != 0) {
		while (m_ImageIndex >= m_Frames.size())
			m_ImageIndex -= (uint32_t)m_Frames.size();
		tex_coords = m_Frames[m_ImageIndex];
	}
	
	m_Vertices[0].TexUV = glm::vec2(tex_coords.x, tex_coords.y);
	m_Vertices[0].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[0].Position = m_Position;

	m_Vertices[1].TexUV = glm::vec2(tex_coords.z, tex_coords.y);
	m_Vertices[1].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[1].Position = m_Position + glm::vec3((float)m_Width,
		0.0f, 0.0f);

	m_Vertices[2].TexUV = glm::vec2(tex_coords.x, tex_coords.w);
	m_Vertices[2].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[2].Position = m_Position + glm::vec3(0.0f,
		(float)m_Height, 0.0f);

	m_Vertices[3].TexUV = glm::vec2(tex_coords.x, tex_coords.w);
	m_Vertices[3].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[3].Position = m_Position + glm::vec3(0.0f,
		(float)m_Height, 0.0f);

	m_Vertices[4].TexUV = glm::vec2(tex_coords.z, tex_coords.y);
	m_Vertices[4].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[4].Position = m_Position + glm::vec3((float)m_Width,
		0.0f, 0.0f);

	m_Vertices[5].TexUV = glm::vec2(tex_coords.z, tex_coords.w);
	m_Vertices[5].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[5].Position = m_Position + glm::vec3((float)m_Width,
		(float)m_Height, 0.0f);
	m_Update = false;
}

bool Sprite::Initialise(const Texture *tex, uint32_t w, uint32_t h,
		const std::vector<uint32_t> &frames)
{
	/* frames contain texture coordinates of all the frames in the sprite if the
	 * sprite is animated, therefore the number of elements need to be dividable
	 * by 4
	 */
	if (frames.size() % 4 != 0 || tex == nullptr)
		return false;

	m_Tex = tex->GetTex();
	m_Texture = tex;
	m_Frames.clear();

	/* OpenGL starts counting Y coordinates from the bottom and up
	 * TidyEngine uses Y coordinates that count from top to bottom
	 * Therefore the Y coordinate needs to be reversed here
	 */
	for (size_t i = 0; i < frames.size(); i += 4) {
		glm::vec4 temp;
		temp.x = (float)frames[i] / (float)m_Texture->GetWidth();
		temp.y = ((float)frames[i + 1] / (float)m_Texture->GetHeight());
		temp.z = (float)frames[i + 2] / (float)m_Texture->GetWidth();
		temp.w = ((float)frames[i + 3] / (float)m_Texture->GetHeight());
		m_Frames.push_back(temp);
	}

	if (w == 0)
		m_Width = m_Texture->GetWidth();
	else
		m_Width = w;
	if (h == 0)
		m_Height = m_Texture->GetHeight();
	else
		m_Height = h;

	m_Update = true;
	
	return true;
}

const glm::vec3 &Sprite::GetPos() const
{
	return m_Position;
}

const uint32_t &Sprite::GetWidth() const
{
	return m_Width;
}

const uint32_t &Sprite::GetHeight() const
{
	return m_Height;
}

void Sprite::SetPos(const glm::vec3 &pos)
{
	m_Position = pos;
	m_Update = true;
}

void Sprite::SetWidth(uint32_t w)
{
	m_Width = w;
	m_Update = true;
}

void Sprite::SetHeight(uint32_t h)
{
	m_Height = h;
	m_Update = true;
}

void Sprite::SetImageIndex(uint32_t image_index)
{
	m_ImageIndex = image_index;
	m_Update = true;
}

void Sprite::SetImageSpeed(float speed)
{
	m_ImageSpeed = speed;
}
