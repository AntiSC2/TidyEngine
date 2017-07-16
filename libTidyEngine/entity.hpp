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

class Entity {
public:
	Entity(std::string name = "temp", std::string script = "none",
	       std::vector<RID> components = {}) : m_Name(name),
		m_Script(script), m_Components(components)
	{
		for (auto i: m_Components) {
			if (i.Data()->Type() == "Renderable")
				m_Graphics.push_back(static_cast<Renderable *>(i.Data()));
		}
	}
	virtual ~Entity();

	virtual void Update(float delta = 0.0f);
	virtual std::vector<Renderable *> &Draw();
	virtual void AddComponents(std::vector<RID> components);
	virtual void RemoveComponents(std::vector<size_t> id);
	virtual RID *GetComponent(size_t id);
	virtual void SetName(std::string name);
	virtual void SetScript(std::string script);
	virtual void SetPos(glm::vec3 pos);
	virtual glm::vec3 GetPos();
protected:
	std::string m_Name = "temp";
	std::string m_Script = "none";
	std::vector<RID> m_Components = {};
	std::vector<Renderable *> m_Graphics = {};
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
};