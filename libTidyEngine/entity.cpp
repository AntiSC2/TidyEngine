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
#include <type_traits>

Entity::~Entity()
{
	;
}

template<typename C>
C &Entity::AddComponent(std::unique_ptr<C> &&component)
{
	static_assert(std::is_base_of<Component, C>::value, "Error: tried to add non-component object to entity!\n");
	auto i = std::type_index(typeid(C));
	m_Components[i] = std::move(component);

	auto &comp = m_Components[i];
	return comp;
}

template<typename C>
void Entity::RemoveComponent()
{
	static_assert(std::is_base_of<Component, C>::value, "Error: tried to remove non-component object from entity!\n");
	auto i = std::type_index(typeid(C));
	auto it = m_Components.find(i);
	if (it != m_Components.end())
		m_Components.erase(it);
}

template<typename C>
C &Entity::GetComponent()
{
	static_assert(std::is_base_of<Component, C>::value, "Error: tried to get non-component object from entity!\n");
	auto i = std::type_index(typeid(C));
	auto &comp = *m_Components[i];
	return comp;
}

const std::string &Entity::GetName()
{
	return m_Name;
}

void Entity::SetName(std::string name)
{
	m_Name = name;
}