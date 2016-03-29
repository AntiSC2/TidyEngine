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
#include <glm/vec2.hpp>
#include "renderable.hpp"
#include "vertex.hpp"
#include "sheet.hpp"

Sprite::Sprite(Sheet *sheet, uint32_t w, uint32_t h)
{
        Initialise(sheet, w, h);
}

Sprite::~Sprite()
{
        ;
}

bool Sprite::Initialise(Sheet *sheet, uint32_t w, uint32_t h)
{
        if (sheet == nullptr)
                return false;

        m_Tex = sheet->GetTex();
        m_TexCoords = sheet->GetTexCoords(0, 0);

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

const std::vector<Vertex> &Sprite::GetVertices()
{
        if (m_Update == true) {
                if (m_Vertices.size() != 6) {
                        m_Vertices.clear();
                        Vertex temp;
                        for (uint8_t i = 0; i < 6; i++)
                                AddVertex(temp);
                }
                m_Vertices[0].TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.w);
                m_Vertices[0].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertices[0].Position = m_Position;

                m_Vertices[1].TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.w);
                m_Vertices[1].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertices[1].Position = m_Position + glm::vec3((float)m_Width,
                        0.0f, 0.0f);

                m_Vertices[2].TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.y);
                m_Vertices[2].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertices[2].Position = m_Position + glm::vec3(0.0f,
                        (float)m_Height, 0.0f);

                m_Vertices[3].TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.y);
                m_Vertices[3].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertices[3].Position = m_Position + glm::vec3(0.0f,
                        (float)m_Height, 0.0f);

                m_Vertices[4].TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.w);
                m_Vertices[4].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertices[4].Position = m_Position + glm::vec3((float)m_Width,
                        0.0f, 0.0f);

                m_Vertices[5].TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.y);
                m_Vertices[5].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertices[5].Position = m_Position + glm::vec3((float)m_Width,
                        (float)m_Height, 0.0f);
                m_Update = false;
        }

        return m_Vertices;
}

void Sprite::SetPos(const glm::vec3 &pos)
{
        m_Position = pos;
        m_Update = true;
}

const glm::vec3 &Sprite::GetPos() const
{
        return m_Position;
}

const uint32_t &Sprite::GetWidth()
{
        return m_Width;
}

const uint32_t &Sprite::GetHeight()
{
        return m_Height;
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
