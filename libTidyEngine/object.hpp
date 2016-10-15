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

#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include "renderable.hpp"
#include "rid.hpp"

class Object {
public:
	Object(std::string name = "temp", std::string script = "none",
	       std::vector<RID> resources = {}) : m_Name(name),
		m_Script(script), m_Resources(resources)
	{
		;
	}
	virtual ~Object();

	virtual void Update(float delta = 0.0f);
	virtual Renderable *Draw();
	void SetName(std::string name);
	void SetScript(std::string script);
protected:
	std::string m_Name = "temp";
	std::string m_Script = "none";
	std::vector<RID> m_Resources = {};
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
};