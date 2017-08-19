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

#include "pointlight.hpp"

PointLight::PointLight()
{
    ;
}

PointLight::~PointLight()
{
    ;
}

std::string PointLight::Type()
{
    return "PointLight";
}

void PointLight::SetPos(glm::vec3 pos)
{
    m_Position = pos;
}

glm::vec3 &PointLight::GetPos()
{
    return m_Position;
}

glm::vec3 &PointLight::GetDiff()
{
    return m_Diffuse;
}

glm::vec3 &PointLight::GetSpec()
{
    return m_Specular;
}

glm::vec3 &PointLight::GetAmbi()
{
    return m_Ambient;
}