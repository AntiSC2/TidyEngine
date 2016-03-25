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

Sheet::Sheet(uint32_t w, uint32_t h, Texture *tex)
{
        Initialise(w, h, tex);
}

Sheet::~Sheet()
{
        m_Tex = nullptr;
}

bool Sheet::Initialise(uint32_t w, uint32_t h, Texture *tex)
{
        if (w == 0 || h == 0 || tex == nullptr)
                return false;
       
        m_Width = w;
        m_Height = h;
        m_Tex = tex;

        m_TexCoords = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        if (m_Tex->GetWidth() > 0 && m_Tex->GetHeight() > 0) {
                m_TexCoords.z = (float)w / (float)m_Tex->GetWidth();
                m_TexCoords.w = (float)h / (float)m_Tex->GetHeight();
        } else {
                m_Width = 0;
                m_Height = 0;
                m_Tex = nullptr;
                return false;
        }
        return true;
}

const GLuint &Sheet::GetTex()
{
        if (m_Tex == nullptr)
                return 0;
        return m_Tex->GetTex();
}
