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

#include "camera2d.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera2D::Camera2D()
{
        ;
}

Camera2D::~Camera2D()
{
        ;
}

/* 
* Always set the scale of the y axis
* to (-m_Scale) because that makes the positive
* y direction to go down the screen
*/
void Camera2D::Initialise(uint16_t width, uint16_t height)
{
        m_Width = width;
        m_Height = height;
        m_Position.x = (float)width/2;
        m_Position.y = (float)height/2;

        m_OrthoMatrix = glm::ortho(0.0f, (float)m_Width, 0.0f, (float)m_Height,
                        0.1f, 100.0f);
        glm::vec3 translate = glm::vec3(-m_Position.x, -m_Position.y, 0.0f);
        m_View = glm::translate(m_View, translate);

        glm::vec3 scale = glm::vec3(m_Scale, -m_Scale, 0.0f);
        m_Model = glm::scale(m_Model, scale);
        m_Update = false;
}

void Camera2D::Update()
{
        if (m_Update == true) {
                glm::vec3 translate = glm::vec3(-m_Position.x, -m_Position.y, 0.0f);
                m_View = glm::translate(m_View, translate);

                glm::vec3 scale = glm::vec3(m_Scale, -m_Scale, 0.0f);
                m_Model = glm::scale(m_Model, scale);
                m_Update = false;
        }
}

void Camera2D::SetScale(float scale)
{
        m_Scale = scale;
        m_Update = true;
}

void Camera2D::SetPosition(glm::vec2 position)
{
        m_Position = position;
        m_Update = true;
}

const float &Camera2D::GetScale() const
{
        return m_Scale;
}

const glm::vec2 &Camera2D::GetPos() const
{
        return m_Position;
}

const glm::mat4 &Camera2D::GetProj() const
{
        return m_OrthoMatrix;
}

const glm::mat4 &Camera2D::GetView() const
{
        return m_View;
}

const glm::mat4 &Camera2D::GetModel() const
{
        return m_Model;
}