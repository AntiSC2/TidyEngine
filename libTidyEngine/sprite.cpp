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
#include <boost/any.hpp>
#include "renderable.hpp"
#include "vertex.hpp"
#include "sheet.hpp"
#include "rid.hpp"

Sprite::Sprite(Sheet *sheet, uint32_t w, uint32_t h,
		const std::vector<uint32_t> &frames)
{
	Initialise(sheet, w, h, frames);
}

Sprite::Sprite(RID *res, uint32_t w, uint32_t h,
	       const std::vector<uint32_t> &frames)
{
	if (res->Data().type().hash_code() == typeid(Sheet *).hash_code()) {
		Sheet *temp = nullptr;
		temp = boost::any_cast<Sheet *>(res->Data());
		Initialise(temp, w, h, frames);
	} else {
		std::printf("%s\n", res->Data().type().name());
	}
}

Sprite::~Sprite()
{
	;
}

void Sprite::Update(bool render)
{
	if (render == true && m_Update == true) {
		if (m_Vertices.size() != 6) {
			m_Vertices.clear();
			Vertex temp;
			for (uint8_t i = 0; i < 6; i++)
				AddVertex(temp);
		}
		if (m_Frames.size() != 0) {
			for (; m_ImageIndex >= m_Frames.size(); m_ImageIndex -=
					(uint32_t)m_Frames.size())
				;
		}
		glm::vec4 tex_coords = m_Frames[m_ImageIndex];
		/* OpenGL starts counting the texture coordinates from the
		 * bottom left corner which makes the textures appear upside
		 * down if we don't reverse the y coordinates here
		 */
		m_Vertices[0].TexUV = glm::vec2(tex_coords.x, tex_coords.w);
		m_Vertices[0].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertices[0].Position = m_Position;

		m_Vertices[1].TexUV = glm::vec2(tex_coords.z, tex_coords.w);
		m_Vertices[1].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertices[1].Position = m_Position + glm::vec3((float)m_Width,
			0.0f, 0.0f);

		m_Vertices[2].TexUV = glm::vec2(tex_coords.x, tex_coords.y);
		m_Vertices[2].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertices[2].Position = m_Position + glm::vec3(0.0f,
			(float)m_Height, 0.0f);

		m_Vertices[3].TexUV = glm::vec2(tex_coords.x, tex_coords.y);
		m_Vertices[3].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertices[3].Position = m_Position + glm::vec3(0.0f,
			(float)m_Height, 0.0f);

		m_Vertices[4].TexUV = glm::vec2(tex_coords.z, tex_coords.w);
		m_Vertices[4].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertices[4].Position = m_Position + glm::vec3((float)m_Width,
			0.0f, 0.0f);

		m_Vertices[5].TexUV = glm::vec2(tex_coords.z, tex_coords.y);
		m_Vertices[5].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertices[5].Position = m_Position + glm::vec3((float)m_Width,
			(float)m_Height, 0.0f);
		m_Update = false;
	} else {
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
}

/* frames must contain an even number of elements, else it returns false */
bool Sprite::Initialise(Sheet *sheet, uint32_t w, uint32_t h,
		const std::vector<uint32_t> &frames)
{
	if (frames.size() % 2 != 0 || sheet == nullptr)
		return false;

	m_Tex = sheet->GetTex();
	m_Frames.clear();
	for (size_t i = 1; i < frames.size(); i += 2)
		m_Frames.push_back(sheet->GetTexCoords(frames[i - 1],
				frames[i]));

	if (w == 0)
		m_Width = sheet->GetWidth();
	else
		m_Width = w;
	if (h == 0)
		m_Height = sheet->GetHeight();
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
