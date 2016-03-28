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

Sheet::Sheet(uint32_t x, uint32_t y, Texture *tex)
{
        Initialise(x, y, tex);
}

Sheet::~Sheet()
{
        m_Tex = nullptr;
}

bool Sheet::Initialise(uint32_t x, uint32_t y, Texture *tex)
{
        if (x == 0 || y == 0 || tex == nullptr)
                return false;
       
        m_TilesX = x;
        m_TilesY = y;
        m_Tex = tex;

        m_TexCoords = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        if (m_Tex->GetWidth() > 0 && m_Tex->GetHeight() > 0) {
                m_TexCoords.z = (float)m_Tex->GetWidth() / (float)x;
                m_TexCoords.w = (float)m_Tex->GetWidth() / (float)y;
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

const glm::vec4 Sheet::GetTexCoords(uint32_t x, uint32_t y) const
{
        if (x == 0 && y == 0)
                return m_TexCoords;
        glm::vec4 temp(m_TexCoords);
        temp.x += m_TexCoords.z * x;
        temp.y += m_TexCoords.w * y;
        temp.z += m_TexCoords.z * x;
        temp.w += m_TexCoords.w * y;
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
