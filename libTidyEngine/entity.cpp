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

void Entity::Update(double delta)
{
	for (auto i : m_Components) {
		i.Data()->Update();
	}
}

std::vector<Renderable *> &Entity::Draw()
{
	return m_Graphics;
}

template<typename C>
void Entity::AddComponents(std::unique_ptr<C> &&component)
{
	m_Components.push_back(component);
}

template<typename C>
void Entity::RemoveComponent()
{
	static_assert(std::is_base_of(Component, C)::value, "Error: tried to remove non-component object!\n");
	m_Components.erase();
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