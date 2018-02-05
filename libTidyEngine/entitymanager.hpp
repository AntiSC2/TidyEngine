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

class Entity;
class IRenderer;

#include <memory>
#include <map>
#include <typeindex>
#include "system.hpp"

class EntityManager {
public:
	EntityManager();
	virtual ~EntityManager();

	virtual void Update();
	template<typename E>
	E &AddEntity(std::unique_ptr<E> &&e);
	Entity &GetEntity(std::string name);
	void RemoveEntity(std::string name);

	template<typename S, typename ...Args>
	S &CreateSystem(Args &&...args);
	void AddSystem(std::unique_ptr<ISystem> &&system, std::type_index i);
	template<typename S>
	S &GetSystem();
	template<typename S>
	void RemoveSystem();
protected:
	std::map<std::type_index, std::unique_ptr<ISystem>> m_Systems;
	std::map<std::string, std::unique_ptr<Entity>> m_Entities;
};

template<typename E>
E &EntityManager::AddEntity(std::unique_ptr<E> &&e)
{
	auto &ent = *e;
	std::string name = ent.GetName();
	static_assert(std::is_base_of<Entity, E>::value, "Error: tried to add non-entity object to manager!\n");

	if (m_Entities.find(name) != m_Entities.end()) {
		printf("Warning: entity %s already exists!\n", name.c_str());
		return ent;
	}

	m_Entities[name] = std::move(e);

	for (auto &i: m_Systems) {
		i.second->AddEntity(e.get());
	}

	return ent;
}

template<typename S, typename ...Args>
S &EntityManager::CreateSystem(Args &&...args)
{
	static_assert(std::is_base_of<ISystem, S>::value, "Error: tried to create a non-system object with manager!\n");	
	S *sys_p = new S(std::forward<Args>(args)...);	
	S &sys = *sys_p;
	sys.SetManager(this);
	AddSystem(std::unique_ptr<ISystem>(static_cast<ISystem*>(sys_p)), std::type_index(typeid(S)));
	return sys;
}

template<typename S>
S &EntityManager::GetSystem()
{
	static_assert(std::is_base_of<ISystem, S>::value, "Error: tried to retrieve non-system object from manager!\n");
	if (m_Systems.find(std::type_index(typeid(S))) == m_Systems.end())
		throw std::runtime_error("Error: could not find system of that type in manager!\n");
	auto &sys = static_cast<S&>(*m_Systems[std::type_index(typeid(S))].get());
	return sys;
}

template<typename S>
void EntityManager::RemoveSystem()
{
	static_assert(std::is_base_of<ISystem, S>::value, "Error: tried to remove non-system object from manager!\n");
	m_Systems.erase(std::type_index(typeid(S)));
}