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

#include <memory>
#include <unordered_map>
#include <string>
#include <typeindex>
#include "component.hpp"
#include "renderable.hpp"

class Entity {
public:
	Entity(std::string name) : m_Name(name) {;}
	virtual ~Entity();

	template<typename C>
	C &AddComponent(std::unique_ptr<C> &&component);
	template<typename C>
	void RemoveComponent();
	template<typename C>
	C &GetComponent();
	const std::string &GetName();
	void SetName(std::string name);
protected:
	std::string m_Name = "";
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;
};

template<typename C>
C &Entity::AddComponent(std::unique_ptr<C> &&component)
{
	auto &comp = *component;
	static_assert(std::is_base_of<Component, C>::value, "Error: tried to add non-component object to entity!\n");
	auto i = std::type_index(typeid(C));
	m_Components[i] = std::move(component);

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

	if (m_Components.find(i) == m_Components.end())
		throw std::runtime_error("Error: could not find component in entity: \"" + m_Name + "\"\n");

	auto &comp = static_cast<C&>(*m_Components[i]);
	return comp;
}