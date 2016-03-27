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

#include <GL/glew.h>
#include <cstdint>
#include <glm/vec4.hpp>

class Sheet {
public:
        /* w and h stand for the sprite size
         * Not the overall size of the texture
         */
        Sheet(uint32_t w = 0, uint32_t h = 0, Texture *tex = nullptr);
        virtual ~Sheet();

        bool Initialise(uint32_t w, uint32_t h, Texture *tex);
        const glm::vec4 &GetTexCoords(uint32_t x, uint32_t y) const;
        const GLuint &GetTex() const; 
        const uint32_t &GetWidth() const;
        const uint32_t &GetHeight() const;
protected:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;

        glm::vec4 m_TexCoords = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        Texture *m_Tex = nullptr;
};
