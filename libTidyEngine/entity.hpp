/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <memory>
#include <map>
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
	bool HasComponent(std::type_index index);
	bool Changed();
	const std::string &GetName();
	void SetName(std::string name);
protected:
	bool m_Change = false;
	std::string m_Name = "";
	std::map<std::type_index, std::unique_ptr<Component>> m_Components;
};

template<typename C>
C &Entity::AddComponent(std::unique_ptr<C> &&component)
{
	auto &comp = *component;
	static_assert(std::is_base_of<Component, C>::value, "Error: tried to add non-component object to entity!\n");
	auto i = std::type_index(typeid(C));
	m_Components[i] = std::move(component);
	m_Change = true;

	return comp;
}

template<typename C>
void Entity::RemoveComponent()
{
	static_assert(std::is_base_of<Component, C>::value, "Error: tried to remove non-component object from entity!\n");
	auto i = std::type_index(typeid(C));
	auto it = m_Components.find(i);
	if (it != m_Components.end()) {
		m_Components.erase(it);
		m_Change = true;
	}
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