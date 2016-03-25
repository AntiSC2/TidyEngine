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
#include "sheet.hpp"

Sprite::Sprite(Sheet *sheet, uint32_t w, uint32_t h)
{
        Initialise(sheet, w, h);
}

Sprite::~Sprite()
{
        
}

bool Sprite::Initalise(Sheet *sheet, uint32_t w, uint32_t h)
{
        if (sheet == nullptr)
                return false;

        m_Tex = sheet->GetTex();
        m_TexCoords = sheet->GetTexCoords();

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

                m_Vertices[0].TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.y);
                m_Vertices[0].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertices[0].Position = m_Position;

                m_Vertices[1].TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.y);
                m_Vertices[1].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertices[1].Position = m_Position + glm::vec3((float)m_Width,
                        0.0f, 0.0f);
        }
}

void Sprite::SetPos(glm::vec3 pos)
{
        m_Position = pos;
        m_Update = true;
}

const glm::vec3 &Sprite::GetPos()
{
        return m_Position;
}
