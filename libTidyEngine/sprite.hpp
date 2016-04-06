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

class Sheet;

#include <cstdint>
#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "renderable.hpp"
#include "vertex.hpp"

class Sprite : public Renderable {
public:
        Sprite(Sheet *sheet, uint32_t w = 0, uint32_t h = 0,
                        const std::vector<uint32_t> &frames = {0, 0});
        virtual ~Sprite();

        virtual void Update(bool render = false);
        virtual bool Initialise(Sheet *sheet, uint32_t w = 0, uint32_t h = 0, 
                        const std::vector<uint32_t> &frames = {0, 0});
        virtual const glm::vec3 &GetPos() const;
        virtual const uint32_t &GetWidth() const;
        virtual const uint32_t &GetHeight() const;
        virtual void SetPos(const glm::vec3 &pos);
        virtual void SetWidth(uint32_t w);
        virtual void SetHeight(uint32_t h);
        virtual void SetImageIndex(uint32_t image_index);
protected:
        float m_ImageSpeed = 0.0f;
        float m_ImageBuffer = 0.0f;
        uint32_t m_ImageIndex = 0;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
        std::vector<glm::vec4> m_Frames;
        bool m_Update = false;
};
