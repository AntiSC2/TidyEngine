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

#include "resource.hpp"
#include <glm/vec3.hpp>

class PointLight: public Resource {
public:
    PointLight();
    ~PointLight();
    virtual std::string Type();

    void SetPos(glm::vec3 pos);
    glm::vec3 &GetPos();
    glm::vec3 &GetDiff();
    glm::vec3 &GetSpec();
    glm::vec3 &GetAmbi();
protected:
    glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_Diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 m_Specular = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 m_Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
};