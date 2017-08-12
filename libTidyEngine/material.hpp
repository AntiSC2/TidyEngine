/*
TidyEngine
Copyright (C) 2017 Jakob Sinclair

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

#include <glm/vec4.hpp>
#include "vertex.hpp"

class Texture;

class Material {
public:
	Material();
	Material(glm::vec4 color);
	Material(std::vector<Texture*> diffuse, std::vector<Texture*> specular);
	virtual ~Material();
protected:
	glm::vec4 m_DiffuseC;
	std::vector<Texture*> m_Diffuse;
	std::vector<Texture*> m_Specular;
};