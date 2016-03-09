﻿/*
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

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <cstdint>

class Camera2D {
public:
        Camera2D();
        ~Camera2D();

        void Initialise(uint16_t width = 0, uint16_t height = 0);
        void Update();
        void SetScale(float scale = 1.0f);
        void SetPosition(glm::vec2 position);
        const float &GetScale() const;
        const glm::vec2 &GetPos() const;
        const glm::mat4 &GetProj() const;
        const glm::mat4 &GetView() const;
        const glm::mat4 &GetModel() const;
private:
        float m_Scale = 1.0f;
        bool m_Update = false;
        uint16_t m_Width = 0;
        uint16_t m_Height = 0;
        glm::vec2 m_Position = glm::vec2(0.0f, 0.0f);
        glm::mat4 m_Model;
        glm::mat4 m_View;
        glm::mat4 m_OrthoMatrix;
};