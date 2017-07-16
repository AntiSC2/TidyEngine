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

#include "entity.hpp"

Entity::~Entity()
{
	;
}

void Entity::Update(float delta)
{
	for (auto i : m_Components) {
		if (i.Data()->Type() == "Renderable") {
			Renderable *temp = static_cast<Renderable *>(i.Data());
			temp->Update(false);
		}
	}
}

std::vector<Renderable *> &Entity::Draw()
{
	return m_Graphics;
}

void Entity::AddComponents(std::vector<RID> components)
{
	m_Components.insert(m_Components.end(), components.begin(), components.end());

	for (auto i: components) {
		if (i.Data()->Type() == "Renderable")
			m_Graphics.push_back(static_cast<Renderable *>(i.Data()));
	}
}

void Entity::RemoveComponents(std::vector<size_t> id)
{
	for (auto i: id) {
		if (i >= m_Components.size())
			continue;

		if (m_Components[i].Data()->Type() == "Renderable")
			m_Graphics.erase(m_Graphics.begin());
		m_Components.erase(m_Components.begin() + i);
	}
}

RID *Entity::GetComponent(size_t id)
{
	if (id >= m_Components.size())
		return nullptr;

	return &m_Components[id];
}

void Entity::SetName(std::string name)
{
	m_Name = name;
}

void Entity::SetScript(std::string script)
{
	m_Script = script;
}

void Entity::SetPos(glm::vec3 pos) 
{
	m_Position = pos;
	for (auto i: m_Graphics) {
		i->SetPos(m_Position);
	}
}

glm::vec3 Entity::GetPos()
{
	return m_Position;
}